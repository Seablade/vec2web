/****************************************************************************
** $Id: rs_vector.h,v 1.13 2004/06/12 23:34:44 andrew Exp $
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


#ifndef RS_VECTOR_H
#define RS_VECTOR_H

#include <iostream>

#include "rs.h"

/**
 * Represents a 3d vector (x/y/z)
 *
 * @author Andrew Mustun
 */
class RS_Vector {
public:
    RS_Vector();
    RS_Vector(double vx, double vy, double vz=0.0);
    //RS_Vector(double v[]);
    explicit RS_Vector(bool valid);
    ~RS_Vector();

    void set(double vx, double vy, double vz=0.0);
    void setPolar(double radius, double angle);

    double distanceTo(const RS_Vector& v) const;
    double angle() const;
    double angleTo(const RS_Vector& v) const;
    double magnitude() const;

	bool isInWindow(const RS_Vector& firstCorner, const RS_Vector& secondCorner);

    RS_Vector move(RS_Vector offset);
    RS_Vector rotate(double ang);
    RS_Vector rotate(RS_Vector center, double ang);
    RS_Vector scale(RS_Vector factor);
    RS_Vector scale(RS_Vector center, RS_Vector factor);
	RS_Vector mirror(RS_Vector axisPoint1, RS_Vector axisPoint2);

    RS_Vector operator + (const RS_Vector& v) const;
    RS_Vector operator - (const RS_Vector& v) const;
    RS_Vector operator * (double s) const;
    RS_Vector operator / (double s) const;
    RS_Vector operator - () const;

    void operator += (const RS_Vector& v);
    void operator -= (const RS_Vector& v);
    void operator *= (double s);

    bool operator == (const RS_Vector& v) const;
    bool operator != (const RS_Vector& v) const {
        return !operator==(v);
    }

    static RS_Vector minimum(const RS_Vector& v1, const RS_Vector& v2);
    static RS_Vector maximum(const RS_Vector& v1, const RS_Vector& v2);
    static RS_Vector crossP(const RS_Vector& v1, const RS_Vector& v2);
    static double dotP(const RS_Vector& v1, const RS_Vector& v2);

    friend std::ostream& operator << (std::ostream&, const RS_Vector& v);

#ifdef RS_TEST

    static bool test();
#endif

public:
    double x;
    double y;
    double z;
    bool valid;
};


/**
 * Represents one to 4 vectors. Typically used to return multiple
 * solutions from a function.
 */
class RS_VectorSolutions {
public:
    RS_VectorSolutions();
    RS_VectorSolutions(const RS_VectorSolutions& s);
    RS_VectorSolutions(int num);
    RS_VectorSolutions(const RS_Vector& v1);
    RS_VectorSolutions(const RS_Vector& v1, const RS_Vector& v2);
    RS_VectorSolutions(const RS_Vector& v1, const RS_Vector& v2,
	                   const RS_Vector& v3);
    RS_VectorSolutions(const RS_Vector& v1, const RS_Vector& v2,
                       const RS_Vector& v3, const RS_Vector& v4);
    RS_VectorSolutions(const RS_Vector& v1, const RS_Vector& v2,
                       const RS_Vector& v3, const RS_Vector& v4,
					   const RS_Vector& v5);
    
	~RS_VectorSolutions();

	void alloc(int num);
    void clean();
    RS_Vector get(int i) const;
	int getNumber() const;
	bool hasValid() const;
	void set(int i, const RS_Vector& v);
	void setTangent(bool t);
    bool isTangent() const;
    RS_Vector getClosest(const RS_Vector& coord, 
			double* dist=NULL, int* index=NULL) const;
    void rotate(RS_Vector center, double ang);
    void scale(RS_Vector center, RS_Vector factor);

	RS_VectorSolutions operator = (const RS_VectorSolutions& s);

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_VectorSolutions& s);

private:
    RS_Vector* vector;
    int num;
    bool tangent;
};

#endif

// EOF
