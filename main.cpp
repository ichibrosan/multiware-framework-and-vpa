////////////////////////////////////////////////////////////////////
// ~/public_html/fw/main.cpp 2025-07-15 18:16 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#include "MP3Player.h"
#include <iostream>
#include <thread>
#include <chrono>

///////////////////////////////////////
// Allocate pointers to user classes //
/*************************************************/

/******************************************************
 * This is the main entry point of the application.
 * It initializes critical components, checks for system
 * requirements, and ensures necessary preconditions
 * are met before running the program's core.
 *
 * @param argc The count of command-line arguments passed.
 * @param argv The array of command-line arguments passed.
 * @return Returns EXIT_SUCCESS if execution completes successfully,
 *         or EXIT_FAILURE if there is an error preventing startup.
 ******************************************************/
int main(int argc, char **argv) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    CLog log(__FILE__,__FUNCTION__);
    log.truncate();

    MP3Player player;

    // Set up a callback to monitor playback events
    player.setPlaybackCallback([](MP3Player::PlaybackState state, double position) {
        std::string stateStr;
        switch (state) {
            case MP3Player::PlaybackState::PLAYING:
                stateStr = "PLAYING";
                break;
            case MP3Player::PlaybackState::PAUSED:
                stateStr = "PAUSED";
                break;
            case MP3Player::PlaybackState::STOPPED:
                stateStr = "STOPPED";
                break;
        }
        std::cout << "State: " << stateStr << ", Position: " << position << "s" << std::endl;
    });

    // Load an MP3 file
    if (!player.loadFile("example.mp3")) {
        std::cerr << "Failed to load MP3 file" << std::endl;
        return 1;
    }

    std::cout << "Loaded file: " << player.getCurrentFilePath() << std::endl;
    std::cout << "Duration: " << player.getDuration() << " seconds" << std::endl;

    // Set volume to 70%
    player.setVolume(0.7f);

    // Play the file
    if (player.play()) {
        std::cout << "Playing..." << std::endl;

        // Let it play for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Pause
        player.pause();
        std::cout << "Paused at position: " << player.getCurrentPosition() << "s" << std::endl;

        // Wait 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Resume
        player.play();
        std::cout << "Resumed..." << std::endl;

        // Let it play for another 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Stop
        player.stop();
        std::cout << "Stopped" << std::endl;
    }







    //gpEnv->extract_username();

    // if(! gpEnv->is_curl_present()) {
    //     log.write("ERROR: curl not installed. Please install the "
    //               "\"curl\" package and re-run this software.");
    //     exit(EXIT_FAILURE);
    // }
    //
    // if(! gpEnv->is_netstat_present()) {
    //     log.write("ERROR: netstat not installed. Please install the "
    //               "\"net-tools\" package and re-run this software.");
    //     exit(EXIT_FAILURE);
    // }

    // gpTest = new test(false,false);
    //
    // gpTest->logHistograms();

    return EXIT_SUCCESS;
}
