# MazeBot
Arduino/ATMega based MazeBot mobile wheeled robot with dc motors controllers, created for a project at Silesian University of Technology.

The construction is actuated by DC motors. The robot avoids obstacles using ultrasonic sensor mounted on top of a servo. To enhace the precision of driving the motors the construction features a PI controller for synchronisation of the wheels velocity and a cascade controller for precision turning.

The project consists of making a custom Arduino Leonardo clone PCB and designing a 3D printable chassis for the construction. Code is implemetned using Arduino libraries and bootloader.

The code and Autodesk Eagle files are stored in the GitHub repository, Autodesk Fusion 360 project files can be accessed using [Autodesk cloud mechanisms](https://a360.co/2U4947x).

We encourage you to check out our documentation and [project report](https://raw.githubusercontent.com/MaciejZj/MazeBot/16cebf032a5ea0aaa41a32081933f3ef379c02ca/Documentation/POLSL_Project_Report_PL.pdf) in Polish.

![khj](https://i.imgur.com/xnGFgQZ.jpg)

The project uses modified [nonblocking ultrasonic Arduino library](https://github.com/jazzycamel/arduino).
