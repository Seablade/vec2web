/****************************************************************************
** $Id: rs_ellipse.cpp,v 1.24 2004/12/26 03:44:27 andrew Exp $
**
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
** This file is part of the qcadlib Library project.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid qcadlib Professional Edition licenses may use 
** this file in accordance with the qcadlib Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.ribbonsoft.com for further details.
**
** Contact info@ribbonsoft.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/


#include "rs_ellipse.h"

#include "rs_graphic.h"
#include "rs_graphicview.h"
#include "rs_painter.h"
#include "rs_information.h"

/**
 * Constructor.
 */
RS_Ellipse::RS_Ellipse(RS_EntityContainer* parent,
                       const RS_EllipseData& d)
        :RS_AtomicEntity(parent), data(d) {

    //calculateEndpoints();
    calculateBorders();
}


/**
 * Recalculates the endpoints using the angles and the radius.
 */
 /*
void RS_Ellipse::calculateEndpoints() {
    double angle = data.majorP.angle();
    double radius1 = getMajorRadius();
    double radius2 = getMinorRadius();

    startpoint.set(data.center.x + cos(data.angle1) * radius1,
                   data.center.y + sin(data.angle1) * radius2);
    startpoint.rotate(data.center, angle);
    endpoint.set(data.center.x + cos(data.angle2) * radius1,
                 data.center.y + sin(data.angle2) * radius2);
    endpoint.rotate(data.center, angle);
}
*/


/**
 * Calculates the boundary box of this ellipse.
 *
 * @todo Fix that - the algorithm used is really bad / slow.
 */
void RS_Ellipse::calculateBorders() {
	RS_DEBUG->print("RS_Ellipse::calculateBorders");

    double radius1 = getMajorRadius();
    double radius2 = getMinorRadius();
    double angle = getAngle();
    double a1 = ((!isReversed()) ? data.angle1 : data.angle2);
    double a2 = ((!isReversed()) ? data.angle2 : data.angle1);
	RS_Vector startpoint = getStartpoint();
	RS_Vector endpoint = getEndpoint();

    double minX = std::min(startpoint.x, endpoint.x);
    double minY = std::min(startpoint.y, endpoint.y);
    double maxX = std::max(startpoint.x, endpoint.x);
    double maxY = std::max(startpoint.y, endpoint.y);

    // kind of a brute force. TODO: calculation
    RS_Vector vp;
	double a = a1;
	do {
        vp.set(data.center.x + radius1 * cos(a),
               data.center.y + radius2 * sin(a));
        vp.rotate(data.center, angle);

        minX = std::min(minX, vp.x);
        minY = std::min(minY, vp.y);
        maxX = std::max(maxX, vp.x);
        maxY = std::max(maxY, vp.y);

		a += 0.03;
    } while (RS_Math::isAngleBetween(RS_Math::correctAngle(a), a1, a2, false) && 
			a<4*M_PI);


    minV.set(minX, minY);
    maxV.set(maxX, maxY);
	RS_DEBUG->print("RS_Ellipse::calculateBorders: OK");
}



RS_VectorSolutions RS_Ellipse::getRefPoints() {
    RS_VectorSolutions ret(getStartpoint(), getEndpoint(), data.center);
    return ret;
}



RS_Vector RS_Ellipse::getNearestEndpoint(const RS_Vector& coord, double* dist) {
    double dist1, dist2;
    RS_Vector nearerPoint;
	RS_Vector startpoint = getStartpoint();
	RS_Vector endpoint = getEndpoint();

    dist1 = startpoint.distanceTo(coord);
    dist2 = endpoint.distanceTo(coord);

    if (dist2<dist1) {
        if (dist!=NULL) {
            *dist = dist2;
        }
        nearerPoint = endpoint;
    } else {
        if (dist!=NULL) {
            *dist = dist1;
        }
        nearerPoint = startpoint;
    }

    return nearerPoint;
}



/**
 * @todo Implement this.
 */
RS_Vector RS_Ellipse::getNearestPointOnEntity(const RS_Vector& coord,
        bool onEntity, double* dist, RS_Entity** entity) {

	RS_DEBUG->print("RS_Ellipse::getNearestPointOnEntity");
    RS_Vector ret(false);

    if (entity!=NULL) {
        *entity = this;
    }

    double step;
    double a1;
    double a2;
    double d;
    double minDist = RS_MAXDOUBLE;

    if (!onEntity) {
        a1 = 0.0;
        a2 = 2*M_PI;
    } else {
        if (!data.reversed) {
            a1 = data.angle1;
            a2 = data.angle2;
        } else {
            a1 = data.angle2;
            a2 = data.angle1;
        }
    }

    // find closest point (approximate)
    RS_Vector vp;
    double bestMatch = 0.0;
    step = 0.01;
    double a = a1+step;
	int eternal = 0;
    do {
		// point on elllipse (wanders from a1 to a2)
        vp.set(data.center.x+cos(a)*getMajorRadius(),
               data.center.y+sin(a)*getMinorRadius());
        vp.rotate(data.center, getAngle());

        d = vp.distanceTo(coord);
        if (d<minDist) {
            minDist = d;
            bestMatch = a;
            ret = vp;
        }

        a += step;
		eternal++;
    } while (eternal<10000 && 
	    RS_Math::isAngleBetween(RS_Math::correctAngle(a), a1, a2, false) &&
		(onEntity || a<2*M_PI));

    // correct:
	/*
    a = bestMatch;
    step = 0.03;
    do {
        vp.set(data.center.x+cos(a)*getMajorRadius(),
               data.center.y+sin(a)*getMinorRadius());
        vp.rotate(data.center, getAngle());

        d = vp.distanceTo(coord);
        if (d<minDist) {
            minDist = d;
            bestMatch = a;
            ret = vp;
        } else {
            // change direction and decrease step amount
            step*=-0.3;
        }

        a += step;
    } while (fabs(step)>1.0e-6);
	*/

    // check endpoints:
    if (onEntity) {
        d = getStartpoint().distanceTo(coord);
        if (d<minDist) {
            ret = getStartpoint();
        }
        d = getEndpoint().distanceTo(coord);
        if (d<minDist) {
            ret = getEndpoint();
        }
    }

    if (dist!=NULL) {
        if (ret.valid) {
            *dist = ret.distanceTo(coord);
        } else {
            *dist = RS_MAXDOUBLE;
        }
    }
	RS_DEBUG->print("RS_Ellipse::getNearestPointOnEntity: OK");

    return ret;
}



/**
 * @param tolerance Tolerance.
 *
 * @retval true if the given point is on this entity.
 * @retval false otherwise
 */
bool RS_Ellipse::isPointOnEntity(const RS_Vector& coord,
                                double tolerance) {
    double dist = getDistanceToPoint(coord, NULL, RS2::ResolveNone);
    return (dist<=tolerance);

	/*
	if (getMajorRadius()<1.0e-6 || getMinorRadius()<1.0e-6) {
		return false;
	}

	RS_Vector v = coord;
	v.rotate(data.center, -getAngle());
	v.move(-data.center);
	double alpha1 = acos(v.x / getMajorRadius());
	double alpha2 = asin(v.y / getMinorRadius());

	std::cout << "alpha1: " << alpha1 << "\n";
	std::cout << "alpha2: " << alpha2 << "\n";

	return (RS_Math::getAngleDifference(alpha1, alpha2)<0.2);
	*/
}



RS_Vector RS_Ellipse::getNearestCenter(const RS_Vector& coord,
                                       double* dist) {
    if (dist!=NULL) {
        *dist = coord.distanceTo(data.center);
    }
    return data.center;
}



/**
 * @todo Implement this.
 */
RS_Vector RS_Ellipse::getNearestMiddle(const RS_Vector& /*coord*/,
                                       double* dist) {
    if (dist!=NULL) {
        *dist = RS_MAXDOUBLE;
    }
    return RS_Vector(false);
}



RS_Vector RS_Ellipse::getNearestDist(double /*distance*/,
                                     const RS_Vector& /*coord*/,
                                     double* dist) {
    if (dist!=NULL) {
        *dist = RS_MAXDOUBLE;
    }
    return RS_Vector(false);
}



/**
 * @todo Implement this.
 */
double RS_Ellipse::getDistanceToPoint(const RS_Vector& coord,
                                      RS_Entity** entity,
                                      RS2::ResolveLevel, double /*solidDist*/) {
    double dist = RS_MAXDOUBLE;
    getNearestPointOnEntity(coord, true, &dist, entity);

    return dist;
}



void RS_Ellipse::move(RS_Vector offset) {
    data.center.move(offset);
    //calculateEndpoints();
    calculateBorders();
}



void RS_Ellipse::rotate(RS_Vector center, double angle) {
    data.center.rotate(center, angle);
    data.majorP.rotate(angle);
    //calculateEndpoints();
    calculateBorders();
}



void RS_Ellipse::moveStartpoint(const RS_Vector& pos) {
	data.angle1 = getEllipseAngle(pos);
	//data.angle1 = data.center.angleTo(pos);
	//calculateEndpoints();
	calculateBorders();
}



void RS_Ellipse::moveEndpoint(const RS_Vector& pos) {
	data.angle2 = getEllipseAngle(pos);
	//data.angle2 = data.center.angleTo(pos);
	//calculateEndpoints();
	calculateBorders();
}


RS2::Ending RS_Ellipse::getTrimPoint(const RS_Vector& coord, 
		const RS_Vector& trimPoint) {
	
	double angEl = getEllipseAngle(trimPoint);
	double angM = getEllipseAngle(coord);

	if (RS_Math::getAngleDifference(angM, angEl)>M_PI) {
		//if (data.reversed) {
		//	return RS2::EndingEnd;
		//}
		//else {
			return RS2::EndingStart;
		//}
	}
	else {
		//if (data.reversed) {
		//	return RS2::EndingStart;
		//}
		//else {
			return RS2::EndingEnd;
		//}
	}
}

double RS_Ellipse::getEllipseAngle(const RS_Vector& pos) {
	RS_Vector m = pos;
	m.rotate(data.center, -data.majorP.angle());
	RS_Vector v = m-data.center;
	v.scale(RS_Vector(1.0, 1.0/data.ratio));
	return v.angle(); 
}



void RS_Ellipse::scale(RS_Vector center, RS_Vector factor) {
    data.center.scale(center, factor);
    data.majorP.scale(factor);
    //calculateEndpoints();
    calculateBorders();
}


/**
 * @todo deal with angles correctly
 */
void RS_Ellipse::mirror(RS_Vector axisPoint1, RS_Vector axisPoint2) {
    RS_Vector mp = data.center + data.majorP;

    data.center.mirror(axisPoint1, axisPoint2);
    mp.mirror(axisPoint1, axisPoint2);

    data.majorP = mp - data.center;

    double a = axisPoint1.angleTo(axisPoint2);

    RS_Vector vec;
    vec.setPolar(1.0, data.angle1);
    vec.mirror(RS_Vector(0.0,0.0), axisPoint2-axisPoint1);
    data.angle1 = vec.angle() - 2*a;

    vec.setPolar(1.0, data.angle2);
    vec.mirror(RS_Vector(0.0,0.0), axisPoint2-axisPoint1);
    data.angle2 = vec.angle() - 2*a;

    data.reversed = (!data.reversed);

    //calculateEndpoints();
    calculateBorders();
}



void RS_Ellipse::moveRef(const RS_Vector& ref, const RS_Vector& offset) {
	RS_Vector startpoint = getStartpoint();
	RS_Vector endpoint = getEndpoint();
	
    if (ref.distanceTo(startpoint)<1.0e-4) {
        moveStartpoint(startpoint+offset);
    }
    if (ref.distanceTo(endpoint)<1.0e-4) {
        moveEndpoint(endpoint+offset);
    }
}


void RS_Ellipse::draw(RS_Painter* painter, RS_GraphicView* view, double patternOffset) {

    if (painter==NULL || view==NULL) {
        return;
    }


    if (getPen().getLineType()==RS2::SolidLine ||
            isSelected() ||
            view->getDrawingMode()==RS2::ModePreview) {

        painter->drawEllipse(view->toGui(getCenter()),
                             getMajorRadius() * view->getFactor().x,
                             getMinorRadius() * view->getFactor().x,
                             getAngle(),
                             getAngle1(), getAngle2(),
                             isReversed());
    } else {
    	double styleFactor = getStyleFactor(view);
		if (styleFactor<0.0) {
        	painter->drawEllipse(view->toGui(getCenter()),
                             getMajorRadius() * view->getFactor().x,
                             getMinorRadius() * view->getFactor().x,
                             getAngle(),
                             getAngle1(), getAngle2(),
                             isReversed());
			return;
		}
		
        // Pattern:
        RS_LineTypePattern* pat;
        if (isSelected()) {
            pat = &patternSelected;
        } else {
            pat = view->getPattern(getPen().getLineType());
        }

        if (pat==NULL) {
            return;
        }

        // Pen to draw pattern is always solid:
        RS_Pen pen = painter->getPen();
        pen.setLineType(RS2::SolidLine);
        painter->setPen(pen);

        double* da;     // array of distances in x.
        int i;          // index counter

        double length = getAngleLength();

        // create pattern:
        da = new double[pat->num];

        double tot=0.0;
        i=0;
        bool done = false;
        double curA = getAngle1();
        double curR;
        RS_Vector cp = view->toGui(getCenter());
        double r1 = getMajorRadius() * view->getFactor().x;
        double r2 = getMinorRadius() * view->getFactor().x;

        do {
            curR = sqrt(RS_Math::pow(getMinorRadius()*cos(curA), 2.0)
                        + RS_Math::pow(getMajorRadius()*sin(curA), 2.0));

            if (curR>1.0e-6) {
                da[i] = fabs(pat->pattern[i] * styleFactor) / curR;
                if (pat->pattern[i] * styleFactor > 0.0) {

                    if (tot+fabs(da[i])<length) {
                        painter->drawEllipse(cp,
                                             r1, r2,
                                             getAngle(),
                                             curA,
                                             curA + da[i],
                                             false);
                    } else {
                        painter->drawEllipse(cp,
                                             r1, r2,
                                             getAngle(),
                                             curA,
                                             getAngle2(),
                                             false);
                    }
                }
            }
            curA+=da[i];
            tot+=fabs(da[i]);
            done=tot>length;

            i++;
            if (i>=pat->num) {
                i=0;
            }
        } while(!done);

        delete[] da;
    }
}



/**
 * Dumps the point's data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_Ellipse& a) {
    os << " Ellipse: " << a.data << "\n";
    return os;
}

