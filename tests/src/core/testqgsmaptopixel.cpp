/***************************************************************************
     testqgsmaptopixel.cpp
     --------------------------------------
    Date                 : Tue  9 Dec 2014
    Copyright            : (C) 2014 by Sandro Santilli
    Email                : strk@keybit.net
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QObject>
//header for class being tested
#include <qgsrectangle.h>
#include <qgsmaptopixel.h>
#include <qgspoint.h>
#include "qgslogger.h"

class TestQgsMapToPixel: public QObject
{
    Q_OBJECT
  private slots:
    void legacy();
};

void TestQgsMapToPixel::legacy()
{
  QgsMapToPixel m2p(2,10,-4,3);

  QgsPoint p(0,0); // in geographical units
  QgsPoint d = m2p.transform(p); // to device pixels
  QCOMPARE( d.x(), -1.5 );
  QCOMPARE( d.y(), 8.0 );

  QgsPoint b = m2p.toMapCoordinatesF( d.x(), d.y() ); // transform back
  QCOMPARE( p, b );

  m2p.transform(&p); // in place transform
  QCOMPARE( p, d );

  m2p.setParameters(0.2, -10, 7, 20);
  p = m2p.toMapCoordinates( -1, -1 );
  QCOMPARE( p.x(), -10.2 );
  QCOMPARE( p.y(), 11.2 );
  d = m2p.transform(p);
  QCOMPARE( d, QgsPoint(-1, -1) );

  p = m2p.toMapCoordinates( 20, 20 );
  QCOMPARE( p.x(), -6.0 );
  QCOMPARE( p.y(), 7.0 );
  d = m2p.transform(p);
  QCOMPARE( d, QgsPoint(20, 20) );

};

QTEST_MAIN( TestQgsMapToPixel )
#include "testqgsmaptopixel.moc"



