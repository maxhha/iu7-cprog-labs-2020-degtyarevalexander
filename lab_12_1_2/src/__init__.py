import tkinter as tk
from src.array import rotate_array, filter_full_squares_array

class Root(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.title("Лаборатонрая работа №12")
        self.option_add( "*font", "monospace 16" )

        self.frame = tk.Frame(self, bd=16)

        self.items_label = tk.Label(self.frame, text="Элементы массива:")
        self.items_entry = tk.Entry(self.frame)

        self.actions_frames = self.__init_actions_frames(self.frame)

        self.error_label = tk.Label(self.frame)
        self.error_label.configure(fg="red")
        self.result_label = tk.Label(self.frame)

        self.items_label.pack(side=tk.TOP, anchor=tk.W)
        self.items_entry.pack(side=tk.TOP, anchor=tk.W)
        self.actions_frames.pack(side=tk.TOP, anchor=tk.W)
        self.error_label.pack(side=tk.TOP, anchor=tk.W)
        self.result_label.pack(side=tk.TOP, anchor=tk.W)

        self.frame.pack()

    def __init_actions_frames(self, root):
        frame = tk.Frame(root)

        self.rotate_action_frame = self.__init_rotate_action_frame(frame)
        self.filter_action_frame = self.__init_filter_action_frame(frame)

        self.rotate_action_frame.pack(side=tk.TOP, anchor=tk.W, pady=4)
        self.filter_action_frame.pack(side=tk.TOP, anchor=tk.W, pady=4)

        return frame

    def __init_rotate_action_frame(self, root):
        frame = tk.Frame(root)

        self.rotate_label = tk.Label(frame, text="Величина сдвига:")
        self.rotate_entry = tk.Entry(frame)
        self.rotate_button = tk.Button(frame, text="Сдвинуть элементы", command=self.__rotate_command)

        self.rotate_label.pack(side=tk.TOP, anchor=tk.W)
        self.rotate_entry.pack(side=tk.TOP, anchor=tk.W)
        self.rotate_button.pack(side=tk.TOP, anchor=tk.W)

        return frame

    def __init_filter_action_frame(self, root):
        frame = tk.Frame(root)

        self.filter_button = tk.Button(frame, text="Отобразить только\nквадраты", command=self.__filter_command)

        self.filter_button.pack(side=tk.TOP, anchor=tk.W)

        return frame

    def __rotate_command(self):
        self.__set_result("")
        self.__set_error("")

        try:
            array = self.__get_array()
            k = self.__get_rotation_n()

            result = rotate_array(array, k)

            self.__set_result(" ".join(map(str, result)))

        except Exception as e:
            self.__set_error(str(e))

    def __filter_command(self):
        self.__set_result("")
        self.__set_error("")

        try:
            array = self.__get_array()

            result = filter_full_squares_array(array)

            self.__set_result(" ".join(map(str, result)))

        except Exception as e:
            self.__set_error(str(e))

    def __get_array(self):
        try:
            return [int(i) for i in self.items_entry.get().split()]
        except:
            raise Exception("Неправильная строка с элементами")

    def __get_rotation_n(self):
        try:
            return int(self.rotate_entry.get())
        except:
            raise Exception("Неправильная строка со сдвигом")

    def __set_result(self, value):
        self.result_label.config(text=value)

    def __set_error(self, value):
        self.error_label.config(text=value)
