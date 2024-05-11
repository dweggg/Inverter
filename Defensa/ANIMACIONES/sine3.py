from manim import *


class ParametricFunction3DExample(ThreeDScene):
    def construct(self):
        self.show_axis()
        self.show_curve()
        self.move_dot_and_draw_curve()
        self.wait()

    def show_axis(self):
        x_start = np.array([-4, -4, 0])
        x_end = np.array([4, -4, 0])

        y_start = np.array([-4, -4, 0])
        y_end = np.array([-4, 4, 0])

        z_start = np.array([-4, -4, 0])
        z_end = np.array([-4, -4, 4])

        x_axis = Line(x_start, x_end)
        y_axis = Line(y_start, y_end)
        z_axis = Line(z_start, z_end)

        self.add(x_axis, y_axis, z_axis)
        self.add_x_labels()
        self.add_y_labels()
        self.add_z_labels()

        self.origin_point = np.array([-4, -4, 0])
        self.curve_start = np.array([-3, -3, 0])

    def add_x_labels(self):
        x_labels = [
            MathTex("-4"), MathTex("-2"), MathTex("0"),
            MathTex("2"), MathTex("4"),
        ]

        for i in range(len(x_labels)):
            x_labels[i].next_to(np.array([-4 + i * 2, -4, 0]), DOWN)
            self.add(x_labels[i])

    def add_y_labels(self):
        y_labels = [
            MathTex("-4"), MathTex("-2"), MathTex("0"),
            MathTex("2"), MathTex("4"),
        ]

        for i in range(len(y_labels)):
            y_labels[i].next_to(np.array([-4, -4 + i * 2, 0]), LEFT)
            self.add(y_labels[i])

    def add_z_labels(self):
        z_labels = [
            MathTex("-4"), MathTex("-2"), MathTex("0"),
            MathTex("2"), MathTex("4"),
        ]

        for i in range(len(z_labels)):
            z_labels[i].next_to(np.array([-4, -4, -4 + i * 2]), OUT)
            self.add(z_labels[i])

    def show_curve(self):
        curve = ParametricFunction(lambda t: [
            np.sin(t),
            np.sin(t + 2 * np.pi / 3),
            np.sin(t - 2 * np.pi / 3)
        ], t_range=[0, 2 * np.pi], color=YELLOW)

        self.add(curve)
        self.curve = curve

    def move_dot_and_draw_curve(self):
        dot = Dot(radius=0.08, color=YELLOW)
        dot.move_to(self.curve.point_from_proportion(0))
        self.t_offset = 0
        rate = 0.25

        def go_around_curve(mob, dt):
            self.t_offset += (dt * rate)
            mob.move_to(self.curve.point_from_proportion(self.t_offset % 1))

        def get_line_to_curve():
            return Line(self.origin_point, dot.get_center(), color=BLUE)

        self.add(dot)
        dot.add_updater(go_around_curve)

        dot_to_curve_line = always_redraw(get_line_to_curve)

        self.add(dot_to_curve_line)
        self.wait(8.5)

        dot.remove_updater(go_around_curve)


# To use the animation:
# scene = ParametricFunction3DExample()
# scene.render()
