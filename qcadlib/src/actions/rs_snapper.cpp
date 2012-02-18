/****************************************************************************
** $Id: rs_snapper.cpp,v 1.24 2005/01/07 16:50:14 andrew Exp $
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


#include "rs_snapper.h"

#include "rs_dialogfactory.h"
#include "rs_entitycontainer.h"
#include "rs_graphic.h"
#include "rs_graphicview.h"
#include "rs_grid.h"
#include "rs_information.h"
#include "rs_mouseevent.h"
#include "rs_painter.h"
#include "rs_settings.h"


/**
 * Constructor.
 */
RS_Snapper::RS_Snapper(RS_EntityContainer& container,
                       RS_GraphicView& graphicView) {
    this->container = &container;
    this->graphicView = &graphicView;
    finished = false;
    init();
}



/**
 * Destructor.
 */
RS_Snapper::~RS_Snapper() {}



/**
 * Initialize (called by all constructors)
 */
void RS_Snapper::init() {
    snapMode = graphicView->getDefaultSnapMode();
    snapRes = graphicView->getSnapRestriction();
    keyEntity = NULL;
    snapSpot = RS_Vector(false);
    snapCoord = RS_Vector(false);
    visible = false;
    distance = 1.0;
    RS_SETTINGS->beginGroup("/Snap");
    snapRange = RS_SETTINGS->readNumEntry("/Range", 20);
    RS_SETTINGS->endGroup();
    RS_SETTINGS->beginGroup("/Appearance");
    showCrosshairs = (bool)RS_SETTINGS->readNumEntry("/ShowCrosshairs", 1);
    RS_SETTINGS->endGroup();
    if (snapRange<2) {
        snapRange = 20;
    }
}

void RS_Snapper::finish() {
    finished = true;
}


/**
 * Snap to a coordinate in the drawing using the current snap mode.
 *
 * @param e A mouse event.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapPoint(RS_MouseEvent* e) {
	RS_DEBUG->print("RS_Snapper::snapPoint");

    deleteSnapper();
    snapSpot = RS_Vector(false);

    if (e==NULL) {
		RS_DEBUG->print(RS_Debug::D_WARNING, 
			"RS_Snapper::snapPoint: event is NULL");
        return snapSpot;
    }

    RS_Vector mouseCoord = graphicView->toGraph(e->x(), e->y());

    switch (snapMode) {

    case RS2::SnapFree:
        snapSpot = snapFree(mouseCoord);
        break;

    case RS2::SnapEndpoint:
        snapSpot = snapEndpoint(mouseCoord);
        break;

    case RS2::SnapGrid:
        snapSpot = snapGrid(mouseCoord);
        break;

    case RS2::SnapOnEntity:
        snapSpot = snapOnEntity(mouseCoord);
        break;

    case RS2::SnapCenter:
        snapSpot = snapCenter(mouseCoord);
        break;

    case RS2::SnapMiddle:
        snapSpot = snapMiddle(mouseCoord);
        break;

    case RS2::SnapDist:
        snapSpot = snapDist(mouseCoord);
        break;

    case RS2::SnapIntersection:
        snapSpot = snapIntersection(mouseCoord);
        break;

    default:
        break;
    }

    // handle snap restrictions that can be activated in addition
    //   to the ones above:
    switch (snapRes) {
    case RS2::RestrictOrthogonal:
        snapCoord = restrictOrthogonal(snapSpot);
        break;
    case RS2::RestrictHorizontal:
        snapCoord = restrictHorizontal(snapSpot);
        break;
    case RS2::RestrictVertical:
        snapCoord = restrictVertical(snapSpot);
        break;
    default:
    case RS2::RestrictNothing:
        snapCoord = snapSpot;
        break;
    }

    drawSnapper();

    if (RS_DIALOGFACTORY!=NULL) {
        RS_DIALOGFACTORY->updateCoordinateWidget(snapCoord,
                snapCoord - graphicView->getRelativeZero());
    }
	
	RS_DEBUG->print("RS_Snapper::snapPoint: OK");

    return snapCoord;
}



/**
 * Snaps to a free coordinate.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapFree(RS_Vector coord) {
    keyEntity = NULL;
    return coord;
}



/**
 * Snaps to the closest endpoint.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapEndpoint(RS_Vector coord) {
    RS_Vector vec(false);

    vec = container->getNearestEndpoint(coord,
                                        NULL/*, &keyEntity*/);
    return vec;
}



/**
 * Snaps to a grid point.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapGrid(RS_Vector coord) {

	RS_DEBUG->print("RS_Snapper::snapGrid begin");

    RS_Vector vec(false);
    double dist=0.0;

    RS_Grid* grid = graphicView->getGrid();
	
	RS_DEBUG->print("RS_Snapper::snapGrid 001");
	
    if (grid!=NULL) {
		RS_DEBUG->print("RS_Snapper::snapGrid 002");
        RS_Vector* pts = grid->getPoints();
		RS_DEBUG->print("RS_Snapper::snapGrid 003");
        int closest = -1;
        dist = 32000.00;
		RS_DEBUG->print("RS_Snapper::snapGrid 004");
        for (int i=0; i<grid->count(); ++i) {
            double d = pts[i].distanceTo(coord);
            if (d<dist) {
                closest = i;
                dist = d;
            }
        }
		RS_DEBUG->print("RS_Snapper::snapGrid 005");
		if (closest>=0) {
        	vec = pts[closest];
		}
		RS_DEBUG->print("RS_Snapper::snapGrid 006");
    }
    keyEntity = NULL;
	
	RS_DEBUG->print("RS_Snapper::snapGrid end");

    return vec;
}



/**
 * Snaps to a point on an entity.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapOnEntity(RS_Vector coord) {

    RS_Vector vec(false);
    vec = container->getNearestPointOnEntity(coord, true, NULL, &keyEntity);
    return vec;
}



/**
 * Snaps to the closest center.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapCenter(RS_Vector coord) {
    RS_Vector vec(false);

    vec = container->getNearestCenter(coord, NULL);
    return vec;
}



/**
 * Snaps to the closest middle.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapMiddle(RS_Vector coord) {
    RS_Vector vec(false);

    vec = container->getNearestMiddle(coord, NULL);
    return vec;
}



/**
 * Snaps to the closest point with a given distance to the endpoint.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapDist(RS_Vector coord) {
    RS_Vector vec(false);

    vec = container->getNearestDist(distance,
                                    coord,
                                    NULL);
    return vec;
}



/**
 * Snaps to the closest intersection point.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapIntersection(RS_Vector coord) {
    RS_Vector vec(false);

    vec = container->getNearestIntersection(coord,
                                            NULL);
    return vec;
}



/**
 * 'Corrects' the given coordinates to 0, 90, 180, 270 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictOrthogonal(RS_Vector coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret(coord);

    RS_Vector retx = RS_Vector(rz.x, ret.y);
    RS_Vector rety = RS_Vector(ret.x, rz.y);

    if (retx.distanceTo(ret) > rety.distanceTo(ret)) {
        ret = rety;
    } else {
        ret = retx;
    }

    return ret;
}

/**
 * 'Corrects' the given coordinates to 0, 180 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictHorizontal(RS_Vector coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret = RS_Vector(coord.x, rz.y);
    return ret;
}


/**
 * 'Corrects' the given coordinates to 90, 270 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictVertical(RS_Vector coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret = RS_Vector(rz.x, coord.y);
    return ret;
}


/**
 * Catches an entity which is close to the given position 'pos'.
 *
 * @param pos A graphic coordinate.
 * @param level The level of resolving for iterating through the entity
 *        container
 * @return Pointer to the entity or NULL.
 */
RS_Entity* RS_Snapper::catchEntity(const RS_Vector& pos,
                                   RS2::ResolveLevel level) {

    RS_DEBUG->print("RS_Snapper::catchEntity");

	// set default distance for points inside solids
    double dist = graphicView->toGraphDX(snapRange)*0.9;

    RS_Entity* entity = container->getNearestEntity(pos, &dist, level);

	int idx = -1;
	if (entity!=NULL && entity->getParent()!=NULL) {
		idx = entity->getParent()->findEntity(entity);
	}

    if (entity!=NULL && dist<=graphicView->toGraphDX(snapRange)) {
        // highlight:
    	RS_DEBUG->print("RS_Snapper::catchEntity: found: %d", idx);
        return entity;
    } else {
    	RS_DEBUG->print("RS_Snapper::catchEntity: not found");
        return NULL;
    }
    RS_DEBUG->print("RS_Snapper::catchEntity: OK");
}



/**
 * Catches an entity which is close to the mouse cursor.
 *
 * @param e A mouse event.
 * @param level The level of resolving for iterating through the entity
 *        container
 * @return Pointer to the entity or NULL.
 */
RS_Entity* RS_Snapper::catchEntity(RS_MouseEvent* e,
                                   RS2::ResolveLevel level) {

    return catchEntity(
               RS_Vector(graphicView->toGraphX(e->x()),
                         graphicView->toGraphY(e->y())),
               level);
}



/**
 * Hides the snapper options. Default implementation does nothing.
 */
void RS_Snapper::hideOptions() {
    if (snapMode==RS2::SnapDist) {
        if (RS_DIALOGFACTORY!=NULL) {
            RS_DIALOGFACTORY->requestSnapDistOptions(distance, false);
        }
    }
}



/**
 * Shows the snapper options. Default implementation does nothing.
 */
void RS_Snapper::showOptions() {
    if (snapMode==RS2::SnapDist) {
        if (RS_DIALOGFACTORY!=NULL) {
            RS_DIALOGFACTORY->requestSnapDistOptions(distance, true);
        }
    }
}



/**
 * Draws the snapper on the screen.
 */
void RS_Snapper::drawSnapper() {
    if (!visible) {
        xorSnapper();
    }
}



/**
 * Deletes the snapper from the screen.
 */
void RS_Snapper::deleteSnapper() {
    if (visible) {
        xorSnapper();
        snapSpot = RS_Vector(false);
        snapCoord = RS_Vector(false);
    }
}



/**
 * Draws / deletes the current snapper spot.
 */
void RS_Snapper::xorSnapper() {
    if (!finished && snapSpot.valid) {
        RS_Painter* painter = graphicView->createDirectPainter();
        painter->setPreviewMode();
        if (snapCoord.valid) {
            // snap point
            painter->drawCircle(graphicView->toGui(snapCoord), 4);

            // crosshairs:
            if (showCrosshairs==true) {
                painter->setPen(RS_Pen(RS_Color(0,255,255),
                                       RS2::Width00, RS2::DashLine));
                painter->drawLine(RS_Vector(0, graphicView->toGuiY(snapCoord.y)),
                                  RS_Vector(graphicView->getWidth(),
                                            graphicView->toGuiY(snapCoord.y)));
                painter->drawLine(RS_Vector(graphicView->toGuiX(snapCoord.x),0),
                                  RS_Vector(graphicView->toGuiX(snapCoord.x),
                                            graphicView->getHeight()));
            }
        }
        if (snapCoord.valid && snapCoord!=snapSpot) {
            painter->drawLine(graphicView->toGui(snapSpot)+RS_Vector(-5,0),
                              graphicView->toGui(snapSpot)+RS_Vector(-1,4));
            painter->drawLine(graphicView->toGui(snapSpot)+RS_Vector(0,5),
                              graphicView->toGui(snapSpot)+RS_Vector(4,1));
            painter->drawLine(graphicView->toGui(snapSpot)+RS_Vector(5,0),
                              graphicView->toGui(snapSpot)+RS_Vector(1,-4));
            painter->drawLine(graphicView->toGui(snapSpot)+RS_Vector(0,-5),
                              graphicView->toGui(snapSpot)+RS_Vector(-4,-1));
        }

        graphicView->destroyPainter();
        visible = !visible;
    }
}

