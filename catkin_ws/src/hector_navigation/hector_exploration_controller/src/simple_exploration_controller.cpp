//=================================================================================================
// Copyright (c) 2012, Stefan Kohlbrecher, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Simulation, Systems Optimization and Robotics
//       group, TU Darmstadt nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================


#include <ros/ros.h>
#include <hector_path_follower/hector_path_follower.h>
#include <hector_nav_msgs/GetRobotTrajectory.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "beginner_tutorials/Loc.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; 

class SimpleExplorationController
{
public:
  SimpleExplorationController()
  {
    //ros::NodeHandle nh;

    exploration_plan_service_client_ = nh.serviceClient<hector_nav_msgs::GetRobotTrajectory>("get_exploration_path");

    path_follower_.initialize(&tfl_);

    //exploration_plan_generation_timer_ = nh.createTimer(ros::Duration(15.0), &SimpleExplorationController::timerPlanExploration, this, false );
    //cmd_vel_generator_timer_ = nh.createTimer(ros::Duration(0.1), &SimpleExplorationController::timerCmdVelGeneration, this, false );

    //vel_pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

    mb_ac = new MoveBaseClient("move_base", true); 

    while(!mb_ac->waitForServer(ros::Duration(5.0))) { 
  ROS_INFO("Waiting for the move_base action server to come up"); 
    }


  }

  ~SimpleExplorationController() 
  {
    delete mb_ac; 
  }

  void timerPlanExploration(const ros::TimerEvent& e)
  {
    hector_nav_msgs::GetRobotTrajectory srv_exploration_plan;

    if (exploration_plan_service_client_.call(srv_exploration_plan)){
      ROS_INFO("Generated exploration path with %u poses", (unsigned int)srv_exploration_plan.response.trajectory.poses.size());
      path_follower_.setPlan(srv_exploration_plan.response.trajectory.poses);
    }else{
      ROS_WARN("Service call for exploration service failed");
    }

    move_base_msgs::MoveBaseGoal goal; 
    goal.target_pose.header.frame_id = "/map"; 
    goal.target_pose.header.stamp = ros::Time::now(); 
    goal.target_pose.pose = srv_exploration_plan.response.trajectory.poses[srv_exploration_plan.response.trajectory.poses.size()-1].pose; 

    ROS_INFO("sending goal"); 
    mb_ac->sendGoal(goal); 
  }

  void timerCmdVelGeneration(const ros::TimerEvent& e)
  {
    geometry_msgs::Twist twist;
    path_follower_.computeVelocityCommands(twist);
    //vel_pub_.publish(twist);
  }

  ros::NodeHandle nh; 

  ros::ServiceClient exploration_plan_service_client_;
  ros::Publisher vel_pub_;

  tf::TransformListener tfl_;

  pose_follower::HectorPathFollower path_follower_;

  ros::Timer exploration_plan_generation_timer_;
  ros::Timer cmd_vel_generator_timer_;

  MoveBaseClient *mb_ac; 

};

//beginner_tutorials::Loc *global_msg; 
beginner_tutorials::Loc global_msg;
vector<vector<float> > odom_msg(4); 

bool saw_a_face; 

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  odom_msg[0].push_back(msg.pose.position.x); 
  odom_msg[1].push_back(msg.pose.position.y); 
  odom_msg[2].push_back(msg.pose.orientation.z); 
  odom_msg[3].push_back(msg.pose.orientation.w)
}

void faceCallback(const beginner_tutorials::Loc::ConstPtr& msg) { 
  if(msg->labels.size() > 0) { 
    ROS_INFO("I heard %f %f %f", msg->x[0], msg->y[0], msg->z[0]);

    //global_msg = new beginner_tutorials::Loc; 

    global_msg.x.push_back(msg->x[0]);
    global_msg.y.push_back(msg->y[0]); 
    global_msg.z.push_back(msg->z[0]);    

    saw_a_face = true; 
  } else { 
    ROS_INFO("I heard nothing"); 

    saw_a_face = false; 
  }

}



int main(int argc, char **argv) {
  ros::init(argc, argv, ROS_PACKAGE_NAME);

  //global_msg = NULL; 

  saw_a_face = false; 

  SimpleExplorationController ec;

  ros::Subscriber subOdom = ec.nh.subscribe("odom", 1, odomCallback)
  ros::Subscriber sub = ec.nh.subscribe("location", 1, faceCallback); 

  ros::Duration(5.0).sleep(); 

  ros::Rate r(0.1); 

  while(ros::ok()) { 
    ros::spinOnce(); 

    if(saw_a_face) { 
  //go to face
  ROS_INFO("camera location: x=%f, y=%f, z=%f, w=%f", odom_msg[odom_msg.size()-1][0], odom_msg[odom_msg.size()-1][1], odom_msg[odom_msg.size()-1][2], odom_msg[odom_msg.size()-1][3]);

  // transform goal 
  


  // set goal 
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = this->x;
  goal.target_pose.pose.position.y = this->y;
  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(this->yaw);

  ROS_INFO("sending goal"); 
  ec.mb_ac->sendGoal(goal); 
  ec.mb_ac->waitForResult(ros::Duration(5.0)); //ros::Duration(10.0)); 
  ec.mb_ac->cancelGoal(); 




    
  //global_msg = NULL; 
    } else { 
  ROS_INFO("go to explore waypoint"); 

  
        hector_nav_msgs::GetRobotTrajectory srv_exploration_plan;
    
        if (ec.exploration_plan_service_client_.call(srv_exploration_plan)){
          ROS_INFO("Generated exploration path with %u poses", (unsigned int)srv_exploration_plan.response.trajectory.poses.size());
          ec.path_follower_.setPlan(srv_exploration_plan.response.trajectory.poses);
        }else{
          ROS_WARN("Service call for exploration service failed");
        }
    
        move_base_msgs::MoveBaseGoal goal; 
        goal.target_pose.header.frame_id = "/map"; 
        goal.target_pose.header.stamp = ros::Time::now(); 
        goal.target_pose.pose = srv_exploration_plan.response.trajectory.poses[srv_exploration_plan.response.trajectory.poses.size()-1].pose; 

        ROS_INFO("sending goal"); 
        ec.mb_ac->sendGoal(goal); 

        ec.mb_ac->waitForResult(ros::Duration(5.0)); //ros::Duration(10.0)); 

  ec.mb_ac->cancelGoal(); 

  
    }
    
    //ROS_INFO("sending goal"); 
    //ec.mb_ac->sendGoal(goal); 

    //ec.mb_ac->waitForResult(); //ros::Duration(10.0)); 

    r.sleep(); 
  }


  //ros::spin();

  return 0;
}
