// Generated by gencpp from file hector_nav_msgs/GetRecoveryInfoRequest.msg
// DO NOT EDIT!


#ifndef HECTOR_NAV_MSGS_MESSAGE_GETRECOVERYINFOREQUEST_H
#define HECTOR_NAV_MSGS_MESSAGE_GETRECOVERYINFOREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace hector_nav_msgs
{
template <class ContainerAllocator>
struct GetRecoveryInfoRequest_
{
  typedef GetRecoveryInfoRequest_<ContainerAllocator> Type;

  GetRecoveryInfoRequest_()
    : request_time()
    , request_radius(0.0)  {
    }
  GetRecoveryInfoRequest_(const ContainerAllocator& _alloc)
    : request_time()
    , request_radius(0.0)  {
    }



   typedef ros::Time _request_time_type;
  _request_time_type request_time;

   typedef double _request_radius_type;
  _request_radius_type request_radius;




  typedef boost::shared_ptr< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetRecoveryInfoRequest_

typedef ::hector_nav_msgs::GetRecoveryInfoRequest_<std::allocator<void> > GetRecoveryInfoRequest;

typedef boost::shared_ptr< ::hector_nav_msgs::GetRecoveryInfoRequest > GetRecoveryInfoRequestPtr;
typedef boost::shared_ptr< ::hector_nav_msgs::GetRecoveryInfoRequest const> GetRecoveryInfoRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hector_nav_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/jade/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/jade/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/jade/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/jade/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3916a0c55958d5dd43204cd2fe5608f6";
  }

  static const char* value(const ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3916a0c55958d5ddULL;
  static const uint64_t static_value2 = 0x43204cd2fe5608f6ULL;
};

template<class ContainerAllocator>
struct DataType< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hector_nav_msgs/GetRecoveryInfoRequest";
  }

  static const char* value(const ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
\n\
\n\
time request_time\n\
float64 request_radius\n\
";
  }

  static const char* value(const ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.request_time);
      stream.next(m.request_radius);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct GetRecoveryInfoRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hector_nav_msgs::GetRecoveryInfoRequest_<ContainerAllocator>& v)
  {
    s << indent << "request_time: ";
    Printer<ros::Time>::stream(s, indent + "  ", v.request_time);
    s << indent << "request_radius: ";
    Printer<double>::stream(s, indent + "  ", v.request_radius);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HECTOR_NAV_MSGS_MESSAGE_GETRECOVERYINFOREQUEST_H
