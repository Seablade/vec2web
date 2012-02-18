/****************************************************************************
** $Id: rs_graphicview.h,v 1.36 2004/09/04 19:56:42 andrew Exp $
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


#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include "rs_entitycontainer.h"

#include <stdarg.h>

#include "rs.h"
#include "rs_blocklist.h"
#include "rs_color.h"
#include "rs_keyevent.h"
#include "rs_linetypepattern.h"
#include "rs_mouseevent.h"
#include "rs_commandevent.h"

class RS_ActionInterface;
//class RS_DimensionData;
//class RS_DimLinearData;
class RS_EventHandler;
class RS_Grid;
class RS_Insert;
class RS_Painter;
class RS_Solid;
class RS_Text;
class RS_Hatch;
//class RS_MirrorData;
//class RS_MoveData;
//class RS_MoveRotateData;
//class RS_Rotate2Data;
//class RS_RotateData;
//class RS_ScaleData;
//class RS_BevelData;
//class RS_RoundData;



/**
 * This class is a common GUI interface for the graphic viewer 
 * widget which has to be implementet by real GUI classes such 
 * as the Qt graphical view.
 *
 * Note that this is just an interface used as a slot to 
 * communicate with the qcadlib from a GUI level. 
 */
class RS_GraphicView {
public:
    RS_GraphicView();
    virtual ~RS_GraphicView();

	void cleanUp();

    /**
     * @return Pointer to the graphic entity if the entity container
     * connected to this view is a graphic and valid.
     * NULL otherwise.
     */
    RS_Graphic* getGraphic() {
        if (container!=NULL && container->rtti()==RS2::EntityGraphic) {
            return (RS_Graphic*)container;
        } else {
            return NULL;
        }
    }

    /**
     * Sets the drawing mode.
     */
    void setDrawingMode(RS2::DrawingMode m) {
        drawingMode = m;
    }

    /**
     * @return Current drawing mode.
     */
    RS2::DrawingMode getDrawingMode() {
        return drawingMode;
    }
	
    /**
     * Activates or deactivates the delete mode.
     */
    void setDeleteMode(bool m) {
        deleteMode = m;
    }

    /**
     * @reval true Deleting instead of drawing.
	 *        false Normal drawing mode.
     */
    bool getDeleteMode() {
        return deleteMode;
    }

    /** This virtual method must be overwritten to return
      the width of the widget the graphic is shown in */
    virtual int getWidth() = 0;
    /** This virtual method must be overwritten to return
      the height of the widget the graphic is shown in */
    virtual int getHeight() = 0;
    /** This virtual method must be overwritten to redraw
      the widget. */
    virtual void redraw() = 0;
    /** This virtual method must be overwritten and is then
      called whenever the view changed */
    virtual void adjustOffsetControls() {}
    /** This virtual method must be overwritten and is then
      called whenever the view changed */
    virtual void adjustZoomControls() {}
	/**
	 * Sets an external painter device.
	 */
    virtual void setPainter(RS_Painter* p) {
		painter = p;
	}
    /** This virtual method must be overwritten and must return
      the painter device for the buffer of this widget */
    virtual RS_Painter* createPainter() = 0;
    /**
     * This virtual method must be overwritten and must return
     *  the direct painter device for this widget 
     */
    virtual RS_Painter* createDirectPainter() = 0;
    /**
     * This virtual method must be overwritten and must destroy
     * the painter device and point 'painter' to NULL. If the painter 
     * is static during the whole life of the application, it might 
     * just do nothing. 
     */
    virtual void destroyPainter() = 0;

    /**
     * Sets the background color. Note that applying the background
     * color for the widget is up to the implementing class.
     */
    virtual void setBackground(const RS_Color& bg) {
        background = bg;

        // bright background:
        if (bg.red()+bg.green()+bg.blue()>380) {
            foreground = Qt::black;
        } else {
            foreground = Qt::white;
        }
    }
	
	/**
	 * @return Current background color.
	 */
	RS_Color getBackground() {
		return background;
	}
	
	/**
	 * @return Current foreground color.
	 */
	RS_Color getForeground() {
		return foreground;
	}

	/**
	 * Sets the grid color.
	 */
	void setGridColor(const RS_Color& c) {
		gridColor = c;
	}

	/**
	 * Sets the meta grid color.
	 */
	void setMetaGridColor(const RS_Color& c) {
		metaGridColor = c;
	}
	
	/**
	 * Sets the selection color.
	 */
	void setSelectedColor(const RS_Color& c) {
		selectedColor = c;
	}
	
	/**
	 * Sets the highlight color.
	 */
	void setHighlightedColor(const RS_Color& c) {
		highlightedColor = c;
	}

    /**
     * This virtual method can be overwritten to set the mouse
     * cursor to the given type.
     */
    virtual void setMouseCursor(RS2::CursorType /*c*/) {}

    void setContainer(RS_EntityContainer* container);
	RS_EntityContainer* getContainer() {
		return container;
	}
    void setFactor(double f) {
		setFactorX(f);
		setFactorY(f);
	}
    void setFactorX(double f);
    void setFactorY(double f);
    //double getFactorX() {
    //    return factor.x;
    //}
    //double getFactorY() {
    //    return factor.y;
    //}
    RS_Vector getFactor() {
        return factor;
    }
    /**
     * Sets the offset of the graphic.
     */
    void setOffset(int ox, int oy) {
        setOffsetX(ox);
        setOffsetY(oy);
    }
    void setOffsetX(int ox) {
        offsetX = ox;
    }
    void setOffsetY(int oy) {
        offsetY = oy;
    }
    int getOffsetX() {
        return offsetX;
    }
    int getOffsetY() {
        return offsetY;
    }
    void centerOffsetX();
    void centerOffsetY();
    void centerX(double x);
    void centerY(double y);
    virtual void updateView();
    /**
     * Sets a fixed border in pixel around the graphic. This border
     * specifies how far the user can scroll outside the graphic
     * area.
     */
    void setBorders(int left, int top, int right, int bottom) {
        borderLeft = left;
        borderTop = top;
        borderRight = right;
        borderBottom = bottom;
    }

    int getBorderLeft() {
        return borderLeft;
    }
    int getBorderTop() {
        return borderTop;
    }
    int getBorderRight() {
        return borderRight;
    }
    int getBorderBottom() {
        return borderBottom;
    }

    void disableUpdate() {
        updateEnabled--;
    }
    void enableUpdate() {
        updateEnabled++;
    }
    bool isUpdateEnabled() {
        return (updateEnabled==0);
    }

    void freezeZoom(bool freeze) {
        zoomFrozen=freeze;
    }
    bool isZoomFrozen() {
        return zoomFrozen;
    }

    void setDefaultAction(RS_ActionInterface* action);
    RS_ActionInterface*  getDefaultAction();
    void setCurrentAction(RS_ActionInterface* action);
    RS_ActionInterface* getCurrentAction();
	
    void killSelectActions();
    void killAllActions();

    /**
     * Must be overwritten to emulate a mouse move event with
     * the last known mouse position.
     *
     * @see mx, my
     */
    virtual void emulateMouseMoveEvent() = 0;

    void back();
    void enter();

    void mousePressEvent(RS_MouseEvent* e);
    void mouseReleaseEvent(RS_MouseEvent* e);
    void mouseMoveEvent(RS_MouseEvent* e);
    void mouseLeaveEvent();
    void mouseEnterEvent();
    void keyPressEvent(RS_KeyEvent* e);
    void keyReleaseEvent(RS_KeyEvent* e);
	void commandEvent(RS_CommandEvent* e);
	void enableCoordinateInput();
	void disableCoordinateInput();

    virtual void zoomIn(double f=1.5, const RS_Vector& center=RS_Vector(false));
    virtual void zoomInX(double f=1.5);
    virtual void zoomInY(double f=1.5);
    virtual void zoomOut(double f=1.5, const RS_Vector& center=RS_Vector(false));
    virtual void zoomOutX(double f=1.5);
    virtual void zoomOutY(double f=1.5);
    virtual void zoomAuto(bool axis=true, bool keepAspectRatio=true);
    virtual void zoomAutoY(bool axis=true);
    virtual void zoomPrevious();
	virtual void saveView();
	virtual void restoreView();
    virtual void zoomWindow(RS_Vector v1, RS_Vector v2,
                            bool keepAspectRatio=true);
    //virtual void zoomPan(RS_Vector v1);
    virtual void zoomPan(int dx, int dy);
    virtual void zoomScroll(RS2::Direction direction);
    virtual void zoomPage();

    virtual void drawWindow(RS_Vector v1, RS_Vector v2);
    virtual void drawIt();
    virtual void deleteEntity(RS_Entity* e);
    virtual void drawEntity(RS_Entity* e, double patternOffset=0.0, bool db=false);
    virtual void drawEntityPlain(RS_Entity* e, double patternOffset=0.0);
    virtual void setPenForEntity(RS_Entity* e);
	
    void simulateIt();
    void simulateEntity(RS_Entity* e, const RS_Pen& pen);
	void drawLineSmooth(const RS_Vector& p1, const RS_Vector& p2, const RS_Pen& pen);
	void drawArcSmooth(const RS_Vector& center, double radius, 
			double a1, double a2, bool rev, const RS_Pen& pen);
	void simulationDelay(bool step=false);

    virtual RS_LineTypePattern* getPattern(RS2::LineType t);

    virtual void drawAbsoluteZero();
    virtual void drawRelativeZero();
    virtual void drawPaper();
    virtual void drawGrid();
    virtual void drawMetaGrid();
    virtual void updateGrid();
    RS_Grid* getGrid() {
        return grid;
    }
	virtual void updateGridStatusWidget(const RS_String& /*text*/) {}

    void setDefaultSnapMode(RS2::SnapMode sm);
    RS2::SnapMode getDefaultSnapMode() {
        return defaultSnapMode;
    }
    void setSnapRestriction(RS2::SnapRestriction sr);
    RS2::SnapRestriction getSnapRestriction() {
        return defaultSnapRes;
    }

    //void showGrid(bool on) {
    //    gridVisible = on;
    //}
    bool isGridOn();

    RS_Vector toGui(RS_Vector v);
    double toGuiX(double x, bool* visible=NULL);
    double toGuiY(double y);
    double toGuiDX(double d);
    double toGuiDY(double d);

    RS_Vector toGraph(RS_Vector v);
    RS_Vector toGraph(int x, int y);
    double toGraphX(int x);
    double toGraphY(int y);
    double toGraphDX(int d);
    double toGraphDY(int d);

	/**
	 * (Un-)Locks the position of the relative zero.
	 *
	 * @param lock true: lock, false: unlock
	 */
	void lockRelativeZero(bool lock) {
		relativeZeroLocked=lock;
	}

	/**
	 * @return true if the position of the realtive zero point is
	 * locked.
	 */
	bool isRelativeZeroLocked() {
		return relativeZeroLocked;
	}

	/**
	 * @return Relative zero coordinate.
	 */
	RS_Vector getRelativeZero() {
		return relativeZero;
	}

	void setRelativeZero(const RS_Vector& pos);
	void moveRelativeZero(const RS_Vector& pos);

	RS_EventHandler* getEventHandler() {
		return eventHandler;
	}

	/**
	 * Enables or disables print preview.
	 */
	void setPrintPreview(bool pv) {
		printPreview = pv;
	}

	/**
	 * @retval true This is a print preview graphic view.
	 * @retval false Otherwise.
	 */
	bool isPrintPreview() {
		return printPreview;
	}
	
	/**
	 * Enables or disables printing.
	 */
	void setPrinting(bool p) {
		printing = p;
	}

	/**
	 * @retval true This is a a graphic view for printing.
	 * @retval false Otherwise.
	 */
	bool isPrinting() {
		return printing;
	}
	
	/**
	 * @retval true Draft mode is on for this view (all lines with 1 pixel / no style scaling).
	 * @retval false Otherwise.
	 */
	bool isDraftMode() {
		return draftMode;
	}

	/** 
	 * Sets the simulation speed in percentage.
	 */
	void setSimulationSpeed(int s) {
		simulationSpeed = s;
	}
	/** 
	 * @return the simulation speed in percentage.
	 */
	int getSimulationSpeed() {
		return simulationSpeed;
	}
	/** 
	 * Sets the simulation smooth mode.
	 */
	void setSimulationSmooth(bool s) {
		simulationSmooth = s;
	}
	/** 
	 * Sets the simulation rapid mode.
	 */
	void setSimulationRapid(bool r) {
		simulationRapid = r;
	}
	/** 
	 * @return the simulation rapid mode.
	 */
	bool getSimulationRapid() {
		return simulationRapid;
	}

protected:
    RS_EntityContainer* container;
    RS_EventHandler* eventHandler;

    int mx;   //!< Last known mouse cursor position
    int my;   //!< Last known mouse cursor position

    RS_Painter* painter;
    /** background color (any color) */
    RS_Color background;
    /** foreground color (black or white) */
    RS_Color foreground;
	/** grid color */
    RS_Color gridColor;
	/** meta grid color */
	RS_Color metaGridColor;
    /** selected color */
    RS_Color selectedColor;
    /** highlighted color */
    RS_Color highlightedColor;
    /** Grid */
    RS_Grid* grid;
    /** 
	 * Current default snap mode for this graphic view. Used for new
	 * actions.
	 */
    RS2::SnapMode defaultSnapMode;
    /** 
	 * Current default snap restriction for this graphic view. Used for new
	 * actions.
	 */
    RS2::SnapRestriction defaultSnapRes;

    RS2::DrawingMode drawingMode;

	/**
	 * Delete mode. If true, all drawing actions will delete in background color
	 * instead.
	 */
	bool deleteMode;
	//! If true, the simulation is currectly running
	bool simulationRunning;

private:
    int updateEnabled;
    bool zoomFrozen;
    //bool gridVisible;
	bool draftMode;

    RS_Vector factor;
	int offsetX;
    int offsetY;
    
	RS_Vector previousFactor;
	int previousOffsetX;
    int previousOffsetY;

    int borderLeft;
    int borderTop;
    int borderRight;
    int borderBottom;

	RS_Vector relativeZero;
	bool relativeZeroLocked;
	//! Print preview flag
	bool printPreview;
	//! Active when printing only:
	bool printing;
	//int drawRecursion;

	//! Simulation speed in percentage
	int simulationSpeed;
 	//! If true, the entity is drawn slowly (pixel by pixel).
	bool simulationSmooth;
 	//! If true, the way between entities is also shown.
	bool simulationRapid;
	//! Last position (for rapid move)
	RS_Vector simulationLast;
};

#endif
