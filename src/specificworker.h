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

/**
       \brief
       @author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <mutex>
#include <atomic>

// includes del openpose

class Cola
{
	public:
		void copyImg(const RoboCompOpenposeServer::ImgType &imgIn)	
				{   std::lock_guard<std::mutex> lock(mutex); 
					img = (cv::Mat)imgIn;
					waiting.store(true);
				};
		
		bool isWaiting() const 							{return waiting.load();};
		void setWaiting(bool v)							{waiting.store(v);};
		bool isReady()   const 							{return ready.load();};
		void setReady(bool v) 	 						{ready.store(v);};
		RoboCompOpenposeServer::Pose getPose() const 	{std::lock_guard<std::mutex> lock(mutex);  return pose;}
		
	private:
		cv::Mat img;
		std::atomic<bool> waiting{true};
		std::atomic<bool> ready{false};
		RoboCompOpenposeServer::Pose pose;

		mutable std::mutex mutex;
};


class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	
	SpecificWorker(MapPrx& mprx);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);

	Pose processImage(const TImage &img);
	

public slots:
	void compute();

private:
	InnerModel *innerModel;
	Cola cola;

};

#endif
