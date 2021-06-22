// Copyright (c) 2018 Samsung Research America
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



#include <string>
#include <memory>
#include <cmath>
#include "cbs_msgs/action/cbspath.hpp"
#include "nav2_behavior_tree/bt_action_node.hpp"


namespace nav2_behavior_tree
{

class CCBSAction : public BtActionNode<cbs_msgs::action::Cbspath>
{
public:
  CCBSAction(
    const std::string & xml_tag_name,
    const std::string & action_name,
    const BT::NodeConfiguration & conf)
  : BtActionNode<cbs_msgs::action::Cbspath>(xml_tag_name, action_name, conf)
  {
    
     getInput("path",goal_.path);
     getInput("timestamp", goal_.timestamp);
  }

  void on_tick() override;

  // Any BT node that accepts parameters must provide a requiredNodeParameters method
  static BT::PortsList providedPorts()
  {
    return providedBasicPorts(
      {
        BT::InputPort<nav_msgs::msg::Path>("path", "Path to goal"),
        BT::InputPort<builtin_interfaces::msg::Time>("timestamp", "Bot has to wait after x seconds")
      });
  }
};

}  // namespace nav2_behavior_tree


#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  BT::NodeBuilder builder =
    [](const std::string & name, const BT::NodeConfiguration & config)
    {
      return std::make_unique<nav2_behavior_tree::CCBSAction>(name, "wait", config);
    };

  factory.registerBuilder<nav2_behavior_tree::CCBSAction>("Wait", builder);
}

