// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "CarlaRecorder.h"
#include "CarlaRecorderHelpers.h"
#include "CarlaRecorderAnimVehicleWheels.h"


// 功能: 将 WheelInfo 对象的数据写入到指定的输出流中
void WheelInfo::Write(std::ostream &OutFile) const
{
    // 写入车辆车轮的位置信息
    // WriteValue 是一个模板函数，用于将指定类型的值写入输出流
    // EVehicleWheelLocation 是车轮位置的枚举类型
    WriteValue<EVehicleWheelLocation>(OutFile, Location);

    // 写入车轮的转向角度
    // SteeringAngle 是一个浮点数，表示车轮的转向角度
    WriteValue<float>(OutFile, SteeringAngle);

    // 写入轮胎的旋转角度
    // TireRotation 是一个浮点数，表示轮胎的旋转角度
    WriteValue<float>(OutFile, TireRotation);
}

void WheelInfo::Read(std::istream &InFile)
{
  ReadValue<EVehicleWheelLocation>(InFile, Location);
  ReadValue<float>(InFile, SteeringAngle);
  ReadValue<float>(InFile, TireRotation);
}

void CarlaRecorderAnimWheels::Write(std::ostream &OutFile)
{
  WriteValue<uint32_t>(OutFile, DatabaseId);
  WriteValue<uint32_t>(OutFile, WheelValues.size());
  for (const WheelInfo& Wheel : WheelValues)
  {
    Wheel.Write(OutFile);
  }
}

void CarlaRecorderAnimWheels::Read(std::istream &InFile)
{
  ReadValue<uint32_t>(InFile, DatabaseId);
  uint32_t NumWheels = 0;
  ReadValue<uint32_t>(InFile, NumWheels);
  WheelValues.resize(NumWheels);
  for (size_t i = 0; i < NumWheels; ++i)
  {
    WheelInfo Wheel;
    Wheel.Read(InFile);
    WheelValues[i] = Wheel;
  }
}

// ---------------------------------------------

void CarlaRecorderAnimVehicleWheels::Clear(void)
{
  VehicleWheels.clear();
}

void CarlaRecorderAnimVehicleWheels::Add(const CarlaRecorderAnimWheels &Vehicle)
{
  VehicleWheels.push_back(Vehicle);
}

void CarlaRecorderAnimVehicleWheels::Write(std::ostream &OutFile)
{
  // 写入数据包 ID
  WriteValue<char>(OutFile, static_cast<char>(CarlaRecorderPacketId::AnimVehicleWheels));

  std::streampos PosStart = OutFile.tellp();

  // 写入虚拟数据包大小
  uint32_t Total = 0;
  WriteValue<uint32_t>(OutFile, Total);

  // 写入总记录数
  Total = VehicleWheels.size();
  WriteValue<uint16_t>(OutFile, Total);

  for (uint16_t i=0; i<Total; ++i)
    VehicleWheels[i].Write(OutFile);

  // 写入实际数据包大小
  std::streampos PosEnd = OutFile.tellp();
  Total = PosEnd - PosStart - sizeof(uint32_t);
  OutFile.seekp(PosStart, std::ios::beg);
  WriteValue<uint32_t>(OutFile, Total);
  OutFile.seekp(PosEnd, std::ios::beg);
}

void CarlaRecorderAnimVehicleWheels::Read(std::istream &InFile)
{
  uint16_t i, Total;
  CarlaRecorderAnimWheels Wheels;

  // 记录车辆总数
  ReadValue<uint16_t>(InFile, Total);
  for (i = 0; i < Total; ++i)
  {
    Wheels.Read(InFile);
    Add(Wheels);
  }
}

const std::vector<CarlaRecorderAnimWheels>& CarlaRecorderAnimVehicleWheels::GetVehicleWheels()
{
  return VehicleWheels;
}
