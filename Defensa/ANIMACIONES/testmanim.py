from manim import *


class PointWithParametricFunction(ThreeDScene):
    def construct(self):
        # Create a 3D cube
        cube = Cube(side_length=2, fill_opacity=0.05, stroke_width=1)

        # Parametric function
        parametric_function = ParametricFunction(lambda t: [
            np.sin(t),
            np.sin(t + 2 * np.pi / 3),
            np.sin(t - 2 * np.pi / 3)
        ], t_range=[0, 2 * np.pi], color=RED)

        # Create a point
        point = Dot(color=YELLOW)

        # Update function for the point
        def update_point(mob, alpha):
            t = alpha * 2 * np.pi
            mob.move_to([
                np.sin(t),
                np.sin(t + 2 * np.pi / 3),
                np.sin(t - 2 * np.pi / 3)
            ])

        # Create an arrow pointing to the point
        arrow = Arrow(ORIGIN, RIGHT, color=BLUE).next_to(point, RIGHT)

        # Update function for the arrow
        def update_arrow(mob):
            mob.put_start_and_end_on(ORIGIN, point.get_center())

        # Begin rotating the camera
        self.begin_ambient_camera_rotation(rate=0.3)

        # Set camera orientation
        self.set_camera_orientation(phi=75 * DEGREES, theta=30 * DEGREES)

        # Play the animation
        self.play(Write(cube), Create(parametric_function), run_time=2)

        # Animate the point along the parametric function
        self.play(UpdateFromAlphaFunc(point, update_point), UpdateFromFunc(arrow, update_arrow), run_time=4)

        # Wait for a moment
        self.wait(5)


# To use the animation:
# scene = PointWithParametricFunction()
# scene.render()
