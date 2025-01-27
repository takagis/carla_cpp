// Copyright (c) 2021 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
// 这是一个头文件保护宏，防止头文件被重复包含
#pragma once  

// 包含各种必要的头文件，用于获取不同类型的Actor相关信息、数学向量、车辆控制设置等相关类和结构体的定义
#include "Actor/ActorInfo.h"
#include "Math/DVector.h"
#include "Carla/Vehicle/AckermannControllerSettings.h"
#include "Carla/Vehicle/VehicleAckermannControl.h"
#include "Carla/Vehicle/VehicleControl.h"
#include "Carla/Vehicle/VehicleLightState.h"
#include "Vehicle/VehicleInputPriority.h"
#include "Vehicle/VehiclePhysicsControl.h"
#include "Carla/Sensor/DataStream.h"
#include "Carla/Traffic/TrafficLightState.h"

// 用于禁用UE4特定的宏定义，可能是为了避免一些预处理器相关的冲突等情况
#include <compiler/disable-ue4-macros.h>
// 包含Carla RPC相关的WalkerControl定义，用于处理行人控制相关内容
#include <carla/rpc/WalkerControl.h>
// 重新启用UE4特定的宏定义
#include <compiler/enable-ue4-macros.h>

// 前置声明类，告诉编译器这些类将会在后续被定义，避免编译时找不到类定义的错误，此处只是声明，无需包含其完整头文件
class UCarlaEpisode; 
class UTrafficLightController;
class FCarlaActor;
#pragma once // 指示编译器此头文件被包含一次，防止重复包含

#include "Actor/ActorInfo.h" // 包含Actor信息相关的声明和定义
#include "Math/DVector.h" // 包含数学向量库，用于表示向量和相关操作
#include "Carla/Vehicle/AckermannControllerSettings.h" // 包含Ackermann控制器设置的相关声明和定义
#include "Carla/Vehicle/VehicleAckermannControl.h" // 包含Ackermann控制相关的声明和定义
#include "Carla/Vehicle/VehicleControl.h" // 包含车辆控制相关的声明和定义
#include "Carla/Vehicle/VehicleLightState.h" // 包含车辆灯光状态的相关声明和定义
#include "Vehicle/VehicleInputPriority.h" // 包含车辆输入优先级的相关声明和定义
#include "Vehicle/VehiclePhysicsControl.h" // 包含车辆物理控制相关的声明和定义
#include "Carla/Sensor/DataStream.h" // 包含数据流类的相关声明和定义
#include "Carla/Traffic/TrafficLightState.h" // 包含交通信号灯状态的相关声明和定义

#include <compiler/disable-ue4-macros.h> // 包含关闭UE4宏的头文件，防止宏冲突
#include <carla/rpc/WalkerControl.h> // 包含行人控制类的相关声明和定义
#include <compiler/enable-ue4-macros.h> // 包含启用UE4宏的头文件，恢复宏定义

class UCarlaEpisode; // 前向声明CARLA Episode类，用于表示仿真会话
class UTrafficLightController; // 前向声明交通灯控制器类，用于控制交通灯
class FCarlaActor; // 前向声明CARLA Actor类，用于表示仿真中的Actor

// FActorData类，作为各种具体Actor数据类的基类，用于存储和操作与Actor相关的通用数据
class FActorData
{
public:
  FDVector Location; // 存储Actor的位置向量
  // 位置信息，使用FDVector类型表示（具体含义可能根据项目自定义
  FDVector Location;

  // 旋转信息，使用FQuat（四元数）类型来表示Actor的旋转状态
  FQuat Rotation;  

  // 缩放信息，使用FVector表示Actor在各个维度上的缩放比例
  FVector Scale;

  // 速度信息，用FVector表示Actor在世界坐标系下的线速度
  FVector Velocity;  

  // 角速度信息，初始化为零向量，表示Actor的旋转速度，默认没有旋转速度
  FVector AngularVelocity = FVector(0,0,0);

  // 布尔值，用于表示是否模拟物理效果，初始化为false，表示默认不模拟物理
  bool bSimulatePhysics = false;

  // 虚函数，用于记录Actor的相关数据，需要在具体子类中实现，参数为指向FCarlaActor对象和UCarlaEpisode对象的指针
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode);

  // 虚函数，用于恢复Actor之前记录的数据，同样需要在具体子类中实现，参数含义同RecordActorData函数
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode);  

  // 虚函数，用于在特定的CarlaEpisode场景中重新生成Actor，参数为CarlaEpisode对象指针和包含Actor信息的FActorInfo对象引用，返回重新生成的AActor对象指针
  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info);

  // 获取本地变换信息（位置、旋转、缩放的组合）的函数，参数为CarlaEpisode对象指针，返回FTransform类型表示的变换信息，此函数被声明为const，表示不会修改对象的内部状态
  FTransform GetLocalTransform(UCarlaEpisode* CarlaEpisode) const;

  // 虚析构函数，用于确保在派生类对象销毁时正确释放资源，为空实现，具体析构逻辑由派生类按需补充
    virtual ~FActorData() {};
  FQuat Rotation; // 存储Actor的旋转四元数

  FVector Scale; // 存储Actor的缩放向量

  FVector Velocity; // 存储Actor的速度向量

  FVector AngularVelocity = FVector(0,0,0); // 存储Actor的角速度，默认值为(0,0,0)

  bool bSimulatePhysics = false; // 指示是否模拟物理行为，默认为false

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode); // 虚函数，用于记录Actor数据
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode); // 虚函数，用于恢复Actor数据
  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info); // 虚函数，用于重新生成Actor
  FTransform GetLocalTransform(UCarlaEpisode* CarlaEpisode) const; // 函数，用于获取Actor的局部变换
  virtual ~FActorData(){}; // 虚析构函数，确保派生类能正确析构
};
// FVehicleData类，继承自FActorData类，用于存储和处理与车辆相关的特定数据
class FVehicleData : public FActorData
{
public:
  FVehiclePhysicsControl PhysicsControl; // 存储车辆物理控制数据
  FVehicleControl Control; // 存储车辆控制数据
  FVehicleAckermannControl AckermannControl; // 存储Ackermann控制数据
};

  // 车辆物理控制相关的数据，包含车辆物理属性的设置等信息
  FVehiclePhysicsControl PhysicsControl;

  // 车辆常规控制相关的数据，例如油门、刹车、转向等控制输入信息
  FVehicleControl Control;  

  // 阿克曼转向控制相关的数据，用于特定的车辆转向控制模式（阿克曼转向常用于车辆模型）
  FVehicleAckermannControl AckermannControl;  

  // 布尔值，用于表示阿克曼转向控制是否处于激活状态，初始化为false
  bool bAckermannControlActive = false;  

  // 阿克曼控制器的设置数据，包含阿克曼转向控制相关的参数配置等信息
  FAckermannControllerSettings AckermannControllerSettings;  

  // 车辆灯光状态数据，用于表示车辆各种灯光（如大灯、转向灯等）的开关状态
  FVehicleLightState LightState;  

  // 车辆速度限制，单位可能根据项目设定，此处初始化为30（默认速度限制值）
  float SpeedLimit = 30;  

  // 车辆故障状态信息，使用carla::rpc::VehicleFailureState类型来表示车辆可能出现的各种故障情况
  carla::rpc::VehicleFailureState FailureState;  

  // 重写基类的RecordActorData函数，用于记录车辆Actor的相关数据，实现特定于车辆的记录逻辑
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;  

  // 重写基类的RestoreActorData函数，用于恢复车辆Actor之前记录的数据，实现特定于车辆的恢复逻辑
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  bool bAckermannControlActive = false; // Ackermann 控制是否激活

  FAckermannControllerSettings AckermannControllerSettings; // Ackermann 控制器设置

  FVehicleLightState LightState; // 车辆灯光状态

  float SpeedLimit = 30; // 车辆速度限制，默认为 30

  carla::rpc::VehicleFailureState FailureState; // 车辆故障状态

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 记录车辆数据

  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 恢复车辆数据
};

// FWalkerData类，继承自FActorData类，用于存储和处理与行人相关的特定数据
class FWalkerData : public FActorData
{
public:
  // 行人控制相关的数据，包含行人行走、转向等控制信息，类型为carla::rpc::WalkerControl
  carla::rpc::WalkerControl WalkerControl;

  // 布尔值，用于表示行人是否处于存活状态，初始化为true，表示默认行人是存活的
  bool bAlive = true;

  // 重写基类的RecordActorData函数，用于记录行人Actor的相关数据，实现特定于行人的记录逻辑
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  // 重写基类的RestoreActorData函数，用于恢复行人Actor之前记录的数据，实现特定于行人的恢复逻辑
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  carla::rpc::WalkerControl WalkerControl; // 行人控制数据

  bool bAlive = true; // 行人是否存活，默认为 true

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 记录行人数据

  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 恢复行人数据
};

// FTrafficSignData类，继承自FActorData类，用于存储和处理与交通标志相关的特定数据
class FTrafficSignData : public FActorData
{
public:
  // 交通标志的唯一标识符，使用FString类型表示
  FString SignId;

  // 交通标志对应的Actor类，使用TSubclassOf<AActor>类型表示，用于在运行时动态创建或查找相应的Actor类
  TSubclassOf<AActor> Model;

  // 交通标志对应的UObject类型的模型，可能用于更具体的资源加载等情况，使用TSubclassOf<UObject>类型表示
  TSubclassOf<UObject> SignModel;

  // 重写基类的RespawnActor函数，用于在CarlaEpisode场景中重新生成交通标志Actor，实现特定于交通标志的重新生成逻辑
  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info) override;

  // 重写基类的RecordActorData函数，用于记录交通标志Actor的相关数据，实现特定于交通标志的记录逻辑
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  // 重写基类的RestoreActorData函数，用于恢复交通标志Actor之前记录的数据，实现特定于交通标志的恢复逻辑
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;
  FString SignId; // 交通标志 ID

  TSubclassOf<AActor> Model; // 标志模型

  TSubclassOf<UObject> SignModel; // 标志对象模型

  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info) override; // 重新生成交通标志

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 记录交通标志数据

  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 恢复交通标志数据
};

// FTrafficLightData类，继承自FActorData类，用于存储和处理与交通信号灯相关的特定数据
class FTrafficLightData : public FActorData
{
public:
    // 指向交通信号灯控制器的指针，用于控制交通信号灯的状态切换等操作，类型为UTrafficLightController*
  UTrafficLightController* Controller;

  // 交通信号灯的当前状态，使用ETrafficLightState枚举类型表示，如红灯、绿灯、黄灯等状态
  ETrafficLightState LightState;

  // 交通信号灯的唯一标识符，使用FString类型表示
  FString SignId;

  // 交通信号灯对应的Actor类，使用TSubclassOf<AActor>类型表示，用于在运行时动态创建或查找相应的Actor类
  TSubclassOf<AActor> Model;

  // 灯杆的索引，可能用于区分多个灯杆或者在特定场景中定位交通信号灯，具体含义根据项目而定
  int PoleIndex;

  // 重写基类的RespawnActor函数，用于在CarlaEpisode场景中重新生成交通信号灯Actor，实现特定于交通信号灯的重新生成逻辑
  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info) override;

  // 重写基类的RecordActorData函数，用于记录交通信号灯Actor的相关数据，实现特定于交通信号灯的记录逻辑
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  // 重写基类的RestoreActorData函数，用于恢复交通信号灯Actor之前记录的数据，实现特定于交通信号灯的恢复逻辑
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;

  UTrafficLightController* Controller; // 交通信号灯控制器

  ETrafficLightState LightState; // 信号灯状态

  FString SignId; // 信号灯 ID

  TSubclassOf<AActor> Model; // 信号灯模型

  int PoleIndex; // 信号灯的杆子索引

  virtual AActor* RespawnActor(UCarlaEpisode* CarlaEpisode, const FActorInfo& Info) override; // 重新生成信号灯

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 记录信号灯数据

  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 恢复信号灯数据
};

// FActorSensorData类，继承自FActorData类，用于存储和处理与Actor传感器相关的特定数据
class FActorSensorData : public FActorData
{
public:

  // 传感器的数据流转对象，用于处理传感器获取的数据，例如图像数据、点云数据等的传输和处理，类型为FDataStream
  FDataStream Stream;

  // 重写基类的RecordActorData函数，用于记录传感器相关Actor的相关数据，实现特定于传感器的记录逻辑
  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;
  FDataStream Stream; // 传感器数据流

  virtual void RecordActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 记录传感器数据

  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override; // 恢复传感器数据
};
sode) override;

  // 重写基类的RestoreActorData函数，用于恢复传感器相关Actor之前记录的数据，实现特定于传感器的恢复逻辑
  virtual void RestoreActorData(FCarlaActor* CarlaActor, UCarlaEpisode* CarlaEpisode) override;
};
