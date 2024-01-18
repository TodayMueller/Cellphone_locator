#include "Locator.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(GetSubscriber, ReturnNulloptIfSubDoesNotExist) {
  Locator locator;
  auto result = locator.GetSubscriber("unknown");
  ASSERT_FALSE(result.has_value());
}

TEST(GetSubscriber, ReturnSubsciberDataIfSuscriberInDb) {
  Locator locator;
  locator.SetSubscriber("+79115555555", 10, 20);
  auto result = locator.GetSubscriber("+79115555555");
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->getX(), 10);
  ASSERT_EQ(result->getY(), 20);
}

TEST(GetSubscriber, ReturnLastSubsciberData) {
  Locator locator;
  locator.SetSubscriber("+79115555555", 10, 20);
  locator.SetSubscriber("+79115555555", -55, -77);
  auto result = locator.GetSubscriber("+79115555555");
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result->getX(), -55);
  ASSERT_EQ(result->getY(), -77);
}

TEST(LoadZones, ReturnLoadedZones) {
  Locator locator;
  locator.load("config.json");
  auto result = locator.zones;

  ASSERT_EQ(result.size(), 2);

  auto zone1It = result.find(1);
  ASSERT_NE(zone1It, result.end());
  EXPECT_EQ(zone1It->second.getName(), "Zone1");

  auto zone2It = result.find(2);
  ASSERT_NE(zone2It, result.end());
  EXPECT_EQ(zone2It->second.getName(), "Zone2");
}

TEST(GetSubsInZone, ReturnSubscriberInZone) {
  Locator locator;
  locator.AddZone(1000, "spb", 0, 0, 20);
  locator.SetSubscriber("+79115555555", 1, 2);
  auto result = locator.GetSubsInZone(1000);
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), "+79115555555");
}

TEST(GetZoneSub, ReturnZoneSub) {
  Locator locator;
  locator.AddZone(1000, "spb", 0, 0, 20);
  locator.SetSubscriber("+79115555555", 1, 2);
  auto result = locator.GetZoneSub("+79115555555");
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result.front(), 1000);
}

TEST(LocatorTest, TriggerUsage) {
  Locator locator;

  locator.AddZoneTrigger("+79115555555", 1, ZoneTrigger::event::ENTER);
  locator.AddProxTrigger("+79115555555", "+79115555554", 10);
  locator.AddZone(1, "spb", 0, 0, 10);
  locator.SetSubscriber("+79115555555", 2, 1);
  locator.SetSubscriber("+79115555554", 3, 4);
  locator.SetSubscriber("+79115555555", 30, 1);
  locator.SetSubscriber("+79115555555", 4, 1);
  locator.SetSubscriber("+79115555555", 2, 2);

  auto proxSubID = locator.proxTriggers.begin()->second.getSubscriber1ID();
  auto zoneSubID = locator.zoneTriggers.begin()->second.getSubID();

  ASSERT_EQ(proxSubID, "+79115555555");
  ASSERT_EQ(zoneSubID, "+79115555555");
}
