#include "easylogging++.h"

// This macro must be placed in exactly one source file
INITIALIZE_EASYLOGGINGPP

// Function to demonstrate different timing scenarios
void performComplexOperation(int iterations) {
    TIMED_FUNC(functionTimer);  // Times the entire function

    // First block with a simple scope
    {
        TIMED_SCOPE(initTimer, "initialization");
        for (int i = 0; i < 100000; ++i) {
            std::string temp = "initializing...";
        }
    }

    // Second block with checkpoints
    TIMED_BLOCK(processTimer, "processing-block") {
        for (int i = 0; i < iterations; ++i) {
            // Simulate some work
            std::vector<int> data(1000, i);
            
            // Add checkpoint every 100 iterations
            if (i % 100 == 0) {
                processTimer.timer->checkpoint(
                    std::string("Iteration-" + std::to_string(i)).c_str()
                );
            }
        }
    }
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);

    // Configure the logger
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    // Enable performance tracking
    defaultConf.set(el::Level::Global,
                   el::ConfigurationType::PerformanceTracking,
                   "true");
    // Apply configuration
    el::Loggers::reconfigureLogger("default", defaultConf);

    // Test 1: Simple timed scope
    {
        TIMED_SCOPE(simpleTimer, "simple-operation");
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Test 2: Timed block with checkpoint
    TIMED_BLOCK(blockTimer, "block-with-checkpoints") {
        // First part of work
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        blockTimer.timer->checkpoint("halfway");
        
        // Second part of work
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Test 3: Complex operation with multiple timers
    performComplexOperation(500);

    return 0;
} 