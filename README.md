# MazeBot
Arduino/ATMega based mobile wheeled robot with DC motors controllers, created for a project at Silesian University of Technology.

![mazebot_demo_photo](https://i.imgur.com/xnGFgQZ.jpg)

The construction is actuated by DC motors. The robot avoids obstacles using an ultrasonic sensor mounted on top of a servo. The robot features a PI controller for synchronisation of the velocity of wheels and a cascade controller for precise turning. These control systems provide greater accuracy of movement, even with the most basic DC motors available.

The project consists of making a custom Arduino Leonardo clone PCB and designing a 3D printable chassis for the construction. Code is implemented using Arduino libraries and the bootloader.

The code and Autodesk Eagle files are stored in the GitHub repository, Autodesk Fusion 360 project files can be accessed using [Autodesk cloud mechanisms](https://a360.co/2U4947x).

Feel free to check out the documentation and [project report](https://raw.githubusercontent.com/MaciejZj/MazeBot/16cebf032a5ea0aaa41a32081933f3ef379c02ca/Documentation/POLSL_Project_Report_PL.pdf) in Polish.

The project uses modified [nonblocking ultrasonic Arduino library](https://github.com/jazzycamel/arduino).
