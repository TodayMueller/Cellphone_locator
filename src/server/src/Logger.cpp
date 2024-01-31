#include "Logger.h"

Logger::Logger(const std::string &configFileName) : logger(initLogger(configFileName)) {}

std::shared_ptr<spdlog::logger> Logger::getLogger() const { return logger; }

std::shared_ptr<spdlog::logger> Logger::initLogger(const std::string &configFileName) {
    nlohmann::json jsonConfig;

    const std::string configFilePath = configFileName;
    if (!std::filesystem::exists(configFilePath)) {
	std::cerr << "Error: Config file not found." << std::endl;
	std::exit(EXIT_FAILURE);
    }

    std::ifstream configFile(configFilePath);
    configFile >> jsonConfig;

    if (jsonConfig.contains("log_level") && jsonConfig["log_level"].is_string()) {
	std::string logLevelStr = jsonConfig["log_level"];
	spdlog::level::level_enum logLevel = spdlog::level::from_str(logLevelStr);

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_st>("Event_log.csv", true);

	auto logger = std::make_shared<spdlog::logger>("main_logger", spdlog::sinks_init_list{file_sink});
	logger->set_level(logLevel);

	return logger;
    }

    return spdlog::stdout_logger_mt("main_logger");
}
