#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  Logger(const std::string &configFileName);

  std::shared_ptr<spdlog::logger> getLogger() const;

private:
  std::shared_ptr<spdlog::logger> initLogger(const std::string &logLevelStr);

  std::shared_ptr<spdlog::logger> logger;
};