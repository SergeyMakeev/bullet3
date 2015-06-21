
#ifndef SHARED_MEMORY_COMMANDS_H
#define SHARED_MEMORY_COMMANDS_H

//this is a very experimental draft of commands. We will iterate on this API (commands, arguments etc)

enum SharedMemoryServerCommand{
    CMD_URDF_LOADING_COMPLETED,
    CMD_URDF_LOADING_FAILED,
	CMD_ACTUAL_STATE_UPDATE_COMPLETED,
//	CMD_DESIRED_STATE_RECEIVED_COMPLETED,
    CMD_STEP_FORWARD_SIMULATION_COMPLETED,
    CMD_MAX_SERVER_COMMANDS
};

enum SharedMemoryClientCommand{
    CMD_LOAD_URDF,
	CMD_REQUEST_ACTUAL_STATE,
//	CMD_SEND_DESIRED_STATE,
    CMD_STEP_FORWARD_SIMULATION, //includes CMD_REQUEST_STATE
    CMD_SHUTDOWN,
    CMD_MAX_CLIENT_COMMANDS
};

#define SHARED_MEMORY_SERVER_TEST_C
#define MAX_DEGREE_OF_FREEDOM 1024
#define MAX_NUM_SENSORS 1024
#define MAX_URDF_FILENAME_LENGTH 1024


struct UrdfArgs
{
    char m_urdfFileName[MAX_URDF_FILENAME_LENGTH];
	bool m_useMultiBody;
	bool m_useFixedBase;
};

struct SendDesiredStateArgs
{
	int m_bodyUniqueId;
};

struct RequestActualStateArgs
{
	int m_bodyUniqueId;
};

struct SendActualStateArgs
{
	int m_bodyUniqueId;
	int m_numDegreeOfFreedomQ;
	int m_numDegreeOfFreedomU;
};


struct StepSimulationArgs
{
    double m_deltaTimeInSeconds;
};

struct SharedMemoryCommand
{
    int m_type;
    
    union
    {
        UrdfArgs m_urdfArguments;
        StepSimulationArgs m_stepSimulationArguments;
		SendDesiredStateArgs m_sendDesiredQandUStateCommandArgument;
		RequestActualStateArgs m_requestActualStateInformationCommandArgument;
		SendActualStateArgs m_sendActualStateArgs;
    };
};


#endif //SHARED_MEMORY_COMMANDS_H
