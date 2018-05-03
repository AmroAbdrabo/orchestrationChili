/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file HexTile.cpp
 * @brief Source for a hexagonal tile definition
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#include "HexTile.h"

#include<QDebug>
#include<QColor>
#include<QSGGeometry>
#include<QSGGeometryNode>
#include<QSGFlatColorMaterial>

#include<cmath>

namespace Cellulo{

HexTile::HexTile(QQuickItem* parent) : QQuickItem(parent){
    q = 0;
    r = 0;

    sourceLeft = 0;
    sourceTop = 0;
    sourceRight = 0;
    sourceBottom = 0;
    sourceCenterX = 0;
    sourceCenterY = 0;

    standardCoords = NULL;

    connect(this, SIGNAL(standardCoordsChanged()), this, SLOT(updateFromStandardCoords()));

    setFlag(QQuickItem::ItemHasContents, true);
    fillColor = QColor(250, 250, 250);
    borderColor = QColor(50, 50, 50);
    borderSize = 0.05;
    connect(this, SIGNAL(fillColorChanged()), this, SLOT(update()));
    connect(this, SIGNAL(borderColorChanged()), this, SLOT(update()));
    connect(this, SIGNAL(borderSizeChanged()), this, SLOT(update()));
}

HexTile::~HexTile(){}

bool HexTile::sourceContains(QVector2D const& point){
    return
        sourceLeft < point.x() &&  point.x() <= sourceRight &&
        sourceTop < point.y() &&   point.y() <= sourceBottom;
}

QVector2D HexTile::hexOffset(float tileWidth){
    return tileWidth*QVector2D(
        (float)q + (float)r*0.5f,
        (float)r*0.86602540378443864676f //sqrt(3)/2
    );
}

QVector2D HexTile::sourceCoordinates(QVector2D const& point){
    return point - QVector2D(sourceLeft + sourceCenterX, sourceTop + sourceCenterY);
}

void HexTile::setStandardCoords(Cellulo::HexTileStandardCoords* standardCoords){
    if(standardCoords != this->standardCoords){
        if(this->standardCoords)
            this->standardCoords->disconnectHexTileChangedSignals(this);
        this->standardCoords = standardCoords;
        if(this->standardCoords)
            this->standardCoords->connectHexTileChangedSignals(this);
        emit standardCoordsChanged();
    }
}

void HexTile::updateFromStandardCoords(){
    if(standardCoords){
        float sourceLeft = standardCoords->getI()*210.0f;
        float sourceRight = sourceLeft;
        float sourceTop = standardCoords->getJ()*260.0f;
        float sourceBottom = sourceTop;
        float sourceCenterX;
        float sourceCenterY;

        if(standardCoords->getU() == 0){
            sourceLeft += 0.0f;
            sourceRight += 105.7f;
            sourceCenterX = 54.3f;
        }
        else{ // == 1
            sourceLeft += 105.7f;
            sourceRight += 210.0f;
            sourceCenterX = 50.0f;
        }

        if(standardCoords->getV() == 0){
            sourceTop += 0.0f;
            sourceBottom += 130.0f;
            sourceCenterY = 67.0f;
        }
        else{ // == 1
            sourceTop += 130.0f;
            sourceBottom += 260.0f;
            sourceCenterY = 67.0f;
        }

        if(this->sourceLeft != sourceLeft){
            this->sourceLeft = sourceLeft;
            emit sourceLeftChanged();
        }
        if(this->sourceRight != sourceRight){
            this->sourceRight = sourceRight;
            emit sourceRightChanged();
        }
        if(this->sourceTop != sourceTop){
            this->sourceTop = sourceTop;
            emit sourceTopChanged();
        }
        if(this->sourceBottom != sourceBottom){
            this->sourceBottom = sourceBottom;
            emit sourceBottomChanged();
        }
        if(this->sourceCenterX != sourceCenterX){
            this->sourceCenterX = sourceCenterX;
            emit sourceCenterXChanged();
        }
        if(this->sourceCenterY != sourceCenterY){
            this->sourceCenterY = sourceCenterY;
            emit sourceCenterYChanged();
        }
    }
}

QSGNode* HexTile::updatePaintNode(QSGNode* oldRoot, UpdatePaintNodeData* updatePaintNodeData){
    Q_UNUSED(updatePaintNodeData);

    qreal w = width();
    qreal h = height();

    QSGNode* root = NULL;
    QSGGeometryNode* hexFill = NULL;
    QSGGeometry* hexFillGeo = NULL;
    QSGGeometryNode* hexBorder = NULL;
    QSGGeometry* hexBorderGeo = NULL;
    qreal borderWidth = w*borderSize;

    //First render
    if(!oldRoot){
        root = new QSGNode();
        hexFill = new QSGGeometryNode();
        hexBorder = new QSGGeometryNode();
        root->appendChildNode(hexFill);
        root->appendChildNode(hexBorder);

        //Hex
        hexFillGeo = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
        hexFillGeo->setLineWidth(0);
        hexFillGeo->setDrawingMode(QSGGeometry::DrawTriangleFan);
        hexFill->setGeometry(hexFillGeo);
        hexFill->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial* hexFillMat = new QSGFlatColorMaterial();
        hexFillMat->setColor(fillColor);
        hexFill->setMaterial(hexFillMat);
        hexFill->setFlag(QSGNode::OwnsMaterial);

        //Border
        hexBorderGeo = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 14);
        hexBorderGeo->setLineWidth(0);
        hexBorderGeo->setDrawingMode(QSGGeometry::DrawTriangleStrip);
        hexBorder->setGeometry(hexBorderGeo);
        hexBorder->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial* hexBorderMat = new QSGFlatColorMaterial();
        hexBorderMat->setColor(borderColor);
        hexBorder->setMaterial(hexBorderMat);
        hexBorder->setFlag(QSGNode::OwnsMaterial);
    }

    //Not the first render
    else{
        root = oldRoot;
        hexFill = static_cast<QSGGeometryNode*>(root->childAtIndex(0));
        hexBorder = static_cast<QSGGeometryNode*>(root->childAtIndex(1));

        //Hex polygon in the background
        hexFillGeo = hexFill->geometry();
        hexFillGeo->allocate(6);
        QSGFlatColorMaterial* hexFillMat = static_cast<QSGFlatColorMaterial*>(hexFill->material());
        hexFillMat->setColor(fillColor);

        //Hex border
        hexBorderGeo = hexBorder->geometry();
        hexBorderGeo->allocate(14);
        QSGFlatColorMaterial* hexBorderMat = static_cast<QSGFlatColorMaterial*>(hexBorder->material());
        hexBorderMat->setColor(borderColor);
    }

    //Hex fill (6 vertices are still enough with triangle fan...)
    QSGGeometry::Point2D* vertices = hexFillGeo->vertexDataAsPoint2D();
    vertices[0].set(0.5*w,              1.15470053837925152902*borderWidth);
    vertices[1].set(w - borderWidth,    0.25*h + 0.57735026918962576451*borderWidth);
    vertices[2].set(w - borderWidth,    0.75*h - 0.57735026918962576451*borderWidth);
    vertices[3].set(0.5*w,              h - 1.15470053837925152902*borderWidth);
    vertices[4].set(borderWidth,        0.75*h - 0.57735026918962576451*borderWidth);
    vertices[5].set(borderWidth,        0.25*h + 0.57735026918962576451*borderWidth);

    //Hex border
    vertices = hexBorderGeo->vertexDataAsPoint2D();
    vertices[0].set(0.5*w,              0);
    vertices[1].set(0.5*w,              1.15470053837925152902*borderWidth);
    vertices[2].set(w,                  0.25*h);
    vertices[3].set(w - borderWidth,    0.25*h + 0.57735026918962576451*borderWidth);
    vertices[4].set(w,                  0.75*h);
    vertices[5].set(w - borderWidth,    0.75*h - 0.57735026918962576451*borderWidth);
    vertices[6].set(0.5*w,  h);
    vertices[7].set(0.5*w,              h - 1.15470053837925152902*borderWidth);
    vertices[8].set(0,      0.75*h);
    vertices[9].set(borderWidth,        0.75*h - 0.57735026918962576451*borderWidth);
    vertices[10].set(0,      0.25*h);
    vertices[11].set(borderWidth,       0.25*h + 0.57735026918962576451*borderWidth);
    vertices[12].set(0.5*w,             0);
    vertices[13].set(0.5*w,             1.15470053837925152902*borderWidth);

    root->markDirty(QSGNode::DirtyGeometry);
    return root;
}

}
