#include <ros/ros.h>
#include <myworkcell_core/LocalizePart.h>

class ScanNPlan
{
public:
  ScanNPlan(ros::NodeHandle& nh_in)
  {
    nh = nh_in;
    vision_client_ = nh.serviceClient<myworkcell_core::LocalizePart>("localize_part");
    nh.param<std::string>("ref_frame_param", ref_frame, "world");
  }

  void start()
  {
    ROS_INFO("Attempting to localize part");
    // Localize the part
    myworkcell_core::LocalizePart srv;
    if (nh.getParam("ref_frame_param", ref_frame));
    srv.request.base_frame = ref_frame;

    if (!vision_client_.call(srv))
    {
      ROS_ERROR("Could not localize part");
      return;
    }
    ROS_INFO_STREAM("part localized: " << srv.response);
  }

private:
  // Planning components
  ros::ServiceClient vision_client_;
  std::string ref_frame;
  ros::NodeHandle nh;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "myworkcell_node");
  ros::NodeHandle nh;
  ros::AsyncSpinner async_spinner (1);

  // Hello World
  ROS_INFO("Hello, World from a ROS Node");

  ScanNPlan app (nh);

  ros::Duration(.5).sleep();

  async_spinner.start();
  app.start();

  ros::spin();
}
