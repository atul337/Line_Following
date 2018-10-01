# Line_Following
Code for a line-following bot having 3 LSA08 (Auto caliberating line sensor) mounted on an octagonal frame having 4 Omni wheel drive.

### Environment
A light (preferably white) colour floor with a 2cm thick line on it. The line resembles the path the robot will follow. The line can bend 90 degrees on either side but there must be no intersections with other paths. This includes + like intersections.

### Behaviour
If the bot is positioned such that atleast one LSA is on a line, it will attempt to track the line and follow it. The bot need not be positioned perfectly, it automatically corrects small deviations.

### Features
- Autonomously follows a line (with 90 degree turns only).
- Corrects small deviations from the line.
- Can rotate by a large (`coarse_rotation`) or a small angle (`fine_rotation`).
