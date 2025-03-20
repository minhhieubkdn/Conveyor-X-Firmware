#include "Communication.h"

CommunicationClass::CommunicationClass()
{
}

void CommunicationClass::init()
{
    COMMAND_PORT.begin(115200);
    inputString.reserve(200);
    isStringCompleted = false;
    inputString = "";
}

void CommunicationClass::execute()
{
    while (COMMAND_PORT.available())
    {
        char inChar = (char)COMMAND_PORT.read();

        if (inChar == '\n')
        {
            isStringCompleted = true;
            break;
        }
        else if (inChar != '\r')
            inputString += inChar;
    }

    if (!isStringCompleted)
        return;

    if (inputString.charAt(0) == 'M')
    {
        parseCommand();
    }

    else if (inputString == "IsXConveyor")
    {
        inputString = "";
        isStringCompleted = false;
        COMMAND_PORT.println("YesXConveyor");
        return;
    }
    else if (inputString == "IsXEncoder")
    {
        COMMAND_PORT.println("YesXEncoder");
        inputString = "";
        isStringCompleted = false;
        return;
    }
    else if (inputString == "UUID")
    {
        COMMAND_PORT.println(Data.uuid);
        inputString = "";
        isStringCompleted = false;
        return;
    }

    inputString = "";
    isStringCompleted = false;
}

void CommunicationClass::parseCommand()
{
    String splitWord = "";
	inputString += " ";
	for (uint16_t i = 0; i < inputString.length(); i++)
	{
		if (inputString[i] == ' ')
		{
			if (splitWord == "")
				continue;

            if (splitWord == "M")
            {
                M = splitWord.substring(1).toFloat();
            }
            else if (splitWord == "R")
            {
                R = splitWord.substring(1).toFloat();
            }
            else if (splitWord == "E")
            {
                E = splitWord.substring(1).toFloat();
            }
            else if (splitWord == "P")
            {
                P = splitWord.substring(1).toFloat();
            }
            else if (splitWord == "S")
            {
                S = splitWord.substring(1).toFloat();
            }
            else if (splitWord == "T")
            {
                T = splitWord.substring(1).toFloat();
            }
			splitWord = "";
			continue;
		}
		splitWord += String(inputString[i]);
	}

    if (M == 310)
    {
        float mode = inputString.substring(5).toFloat();
        if (S < Data.max_speed)
        {
            Stepper.setMode(bool(mode));
            COMMAND_PORT.println("Ok");
        }
        else
        {
            COMMAND_PORT.println("Error: Exceeds max speed!");
        }
    }
    else if (M == 311)
    {
        if (S < Data.max_speed)
        {
            Stepper.setSpeed(S);
            COMMAND_PORT.println("Ok");
        }
        else
        {
            COMMAND_PORT.println("Error: Exceeds max speed!");
        }
    }

    else if (M == 312)
    {
        float position = inputString.substring(5).toFloat();
        Stepper.setDesirePosition(position);
        COMMAND_PORT.println("Ok");
    }

    else if (M == 313)
    {
        float position_speed = inputString.substring(5).toFloat();
        if (position_speed < Data.max_speed)
        {
            Stepper.setPositionSpeed(position_speed);
            COMMAND_PORT.println("Ok");
        }
        else
        {
            COMMAND_PORT.println("Error: Exceeds max speed!");
        }
    }
    else if (M == 315)
    {
        if (S != NULL_NUMBER)
        {
            Stepper.setStepPerMM(S);
            COMMAND_PORT.println("Ok");
        }

        if (R != NULL_NUMBER)
        {
            Stepper.setInvertDir(R);
            COMMAND_PORT.println("Ok");
        }

        if (E != NULL_NUMBER)
        {
            Stepper.setStepperEnable(E);
            COMMAND_PORT.println("Ok");
        }
    }
    else if (M == 316)
    {
        float mode = inputString.substring(5).toFloat();
        if (mode < 2 && mode > -1)
        {
            Encoder.setMode(bool(mode));
            COMMAND_PORT.println("Ok");
        }
        else
        {
            COMMAND_PORT.println("Unknown: Invalid mode!");
        }
    }
    else if (M == 317)
    {
        if (T == NULL_NUMBER)
        {
            Encoder.getCurrentPosition();
        }
        else
        {
            Encoder.setAutoReadPeriod(T);
            COMMAND_PORT.println("Ok");
        }
    }
    else if (M == 318)
    {
        if (S != NULL_NUMBER)
        {
            Encoder.setPulsePerMM(S);
        }
        if (R != NULL_NUMBER)
        {
            Encoder.setInvertDir(R);
        }
        
        if (S == NULL_NUMBER && R == NULL_NUMBER)
        {   
            COMMAND_PORT.print("S");
            COMMAND_PORT.print(Encoder.pulse_per_mm);
            COMMAND_PORT.print(" R");
            COMMAND_PORT.println(Encoder.invert_encoder_dir);
        }
        
    }
}

void CommunicationClass::resetParameters()
{
    M = R = E = P = S = NULL_NUMBER;
}

CommunicationClass Communication;