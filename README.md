# Redhill_D_Kovanov


## Setup
**Requirements**
- Unreal Engine 5.6.1
- Microsoft Visual Studio 2022 C++ Build Tools (MSVC v143, Windows SDK, and required .NET SDK)
- Git
- Git LFS

**Recommended IDE**
- JetBrains Rider 2025.3.3 (used during development)
- Visual Studio 2022 is also supported.

**Setup Instructions**
1. Download and install Git if it isn't already installed.
2. Download and install Git LFS.
   Once installed, open Git Bash or Command Prompt and run "git lfs install" to initialize Git LFS to your account.
4. Open Git Bash or Command Prompt and navigate to the directory where you'd like to store the project.
   Run "git clone https://github.com/DKovanov01/Redhill_D_Kovanov.git" to download the project.
6. Navigate into the cloned project directory and ensure all tracked assets have been downloaded with the command "git lfs pull".
7. Open "Redhill_D_Kovanov.uproject" using Unreal Engine 5.6.1.
8. Allow Unreal Engine to rebuild the project modules if prompted.
   If compilation fails, close the Unreal Editor, right-click "Redhill_D_Kovanov.uproject" and select Generate Visual Studio project files.
   Open the generated solution in your preferred IDE, select "Development Editor" configuration and "Win64" platform.
   Build Redhill_D_KovanovEditor target.
   Once compilation succeeds, run "Redhill_D_Kovanov.uproject" again.

Note: Downloading the repo as a ZIP is not recommended, as git LFS files may not be retrieved properly.

**Gameplay Instructions**
- Movement: "W", "A", "S", "D";
- Jump: "Space";
- Interaction Key: "E";
- Reset Key: "F";
- Close Game: "Esc";

To complete the game, reach the lever on the right side of the room, interact with it to open the door, and leave the room;

**Implementation Decisions**

The project was built upon UE5's Third Person template to save time on integrating base assets and player movement;

Although the original plan was to primarily use Blueprints, while C++ was reserved for specific implementations, such as the door's functionality, I gradually shifted towards focusing more on C++. Having had limited prior experience with C++, I wanted to explore how it could be used alongside Blueprints to better understand interactions between the two systems. 

For example, the Player Character is implemented mostly in C++, while its interaction collision sphere which was configured through Blueprints; Other actors, such as the Lever and Side Camera, although originally implemented through Blueprints, were migrated fully to C++ with Blueprint-callable functions used where appropriate.

Once I understood the fundamentals of C++, I continued using Blueprints for many of the interactions and conditions between actors, particularly those involving the Player and Lever. This allowed me to work with familiar tools while keeping the final interaction between the Lever and Door, as per instructions, in C++.

**Known Issues**

Issue #1 - Door Collision Box; Originally added for testing & debugging with the purpose of making sure the door opened upon collision with the player, the collision box became obsolete when the door's opening interaction was moved to the lever. However, attempts to remove the door's collision box, which was implemented in C++, resulted in compilation errors and Unreal Editor crashing upon launch, so while the collision box no longer has functionality to it, it still exists, and floats far above the door.

Issue #2 - The door's opening is done through a Curve Asset; While the speed with which it opens can be edited through the editor successfully, there is a disconnect between the value accepted as rotation degrees - the Curve Asset by default makes the door rotate -90 degrees, however in C++ that value is equal to 1.0f - with values set higher or lower making the door rotate -90 * Value, so setting it to 10.0f would make the door turn -90 degrees 10 times. To avoid this interaction causing issues in testing or gameplay, this particular setting cannot be edited in the editor and will always remain 1.0f;

**Resources Used**

For assets, only Unreal Engine 5's base Third Person Template assets were used;

For learning & code, usage varies between official Unreal Engine 5 documentation, video tutorials, and AI (ChatGPT);

AI Use: ChatGPT was first used in the first hour of the project to debug issues that were a result of original IDE used for C++, as well as compilation and crashes; ChatGPT was later used again starting from hour 3, interchangeably with other sources, to both further my understanding of C++ and Blueprint interacions (which had limited effect due to its inaccuracy) and in debugging compilation issues;

**Time Spent**

5 hours and 57 minutes;

**Demo Video**

https://youtu.be/EckfRFhRt9I
