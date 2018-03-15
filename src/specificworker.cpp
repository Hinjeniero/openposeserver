/*
 *    Copyright (C)2018 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	futur = std::async(std::launch::async, &Openpose::wrapper, openpose);
	//timer.start(Period);
	return true;
}

void SpecificWorker::compute()
{
	qDebug() << "hola";
	if(cola.isWaiting())
	{
		cola.setWaiting(false);
		//std::this_thread::sleep_for(1ms);
		sleep(1);
		qDebug() << "imagen procesada";
		//copiar pòse a cola
		cola.setReady(true);
	}
}

////////////////////////////////////////////////////////////////////
////////////// SERVANT /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

Pose SpecificWorker::processImage(const TImage &img)
{
	cola.copyImg(img.image);
	qDebug() << "imagen recibida";
	// while(!cola.isReady();
	cola.setReady(false);
	return cola.getPose();

}


