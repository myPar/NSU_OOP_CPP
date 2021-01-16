#include "Runner.h"

void Runner::run(int argc, char* argv[]) {
	GameLauncher launcher;
	GameSettings settings = launcher.parse_settings(argc, argv);

	GameExecutor executor;
	executor.execute(settings);
}
