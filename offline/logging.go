package main

import (
	"go.uber.org/zap"
)

// ------------------------------------------------------------------------------------------------
// custom "dev" mode; disabling caller and stacktrace as it can get overwhelming
func customLogConfig() zap.Config {
	return zap.Config{
		Level:             zap.NewAtomicLevelAt(zap.InfoLevel),
		Development:       true,
		DisableCaller:     true,
		DisableStacktrace: true,
		Encoding:          "console",
		EncoderConfig:     zap.NewDevelopmentEncoderConfig(),
		OutputPaths:       []string{"stderr"},
		ErrorOutputPaths:  []string{"stderr"},
	}
}

// SysLog is the app-wide log output
var SysLog, _ = customLogConfig().Build()
