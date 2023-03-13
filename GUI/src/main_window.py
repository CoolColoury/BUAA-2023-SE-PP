import sys
from ctypes import cdll, c_char_p, c_int, c_char, c_bool

from PyQt5.QtWidgets import QMainWindow, QApplication, QFileDialog
import qdarkstyle

from ui.main import Ui_MainWindow


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.import_txt_button.clicked.connect(self.import_txt)
        self.clear_button.clicked.connect(self.clear)
        self.solve_button.clicked.connect(self.solve)
        self.export_txt_button.clicked.connect(self.export_txt)

    def import_txt(self):
        file_dialog = QFileDialog()
        file_name, _ = file_dialog.getOpenFileName(None, "Select File", "", "Text Files(*.txt)")
        if file_name:
            with open(file_name, 'r') as file:
                self.input_text.setText(file.read())
        return

    def clear(self):
        self.input_text.clear()
        return

    def solve(self):
        core_dll = cdll.LoadLibrary("..\\dll\\core.dll")
        index = self.tabWidget.currentIndex()

        words = self.input_text.toPlainText().split()
        len_w = len(words)

        c_words = (c_char_p * len_w)()
        for i in range(len_w):
            c_words[i] = words[i].encode('utf-8')

        c_len = c_int(len(words))

        result = (c_char_p * 20000)()

        if index == 0:
            ans = core_dll.gen_chains_all(c_words, c_len, result)
            results = [result[i].decode('utf-8') for i in range(ans)]
            text = '\n'.join(results)
            self.output_text.setText(text)
        elif index == 1:
            h = self.w_h_box.currentText()
            c_h = c_char(0) if h == '无' else c_char(h[0].encode('utf-8'))
            t = self.w_t_box.currentText()
            c_t = c_char(0) if t == '无' else c_char(t[0].encode('utf-8'))
            n_h = self.w_j_box.currentText()
            c_n_h = c_char(0) if n_h == '无' else c_char(n_h[0].encode('utf-8'))
            c_r = c_bool(self.w_r_check.isChecked())
            ans = core_dll.gen_chain_word(c_words, c_len, result, c_h, c_t, c_n_h, c_r)
            results = [result[i].decode('utf-8') for i in range(ans)]
            text = '\n'.join(results)
            self.output_text.setText(text)
        elif index == 2:
            h = self.c_h_box.currentText()
            c_h = c_char(0) if h == '无' else c_char(h[0].encode('utf-8'))
            t = self.c_t_box.currentText()
            c_t = c_char(0) if t == '无' else c_char(t[0].encode('utf-8'))
            n_h = self.c_j_box.currentText()
            c_n_h = c_char(0) if n_h == '无' else c_char(n_h[0].encode('utf-8'))
            c_r = c_bool(self.c_r_check.isChecked())
            ans = core_dll.gen_chain_char(c_words, c_len, result, c_h, c_t, c_n_h, c_r)
            results = [result[i].decode('utf-8') for i in range(ans)]
            text = '\n'.join(results)
            self.output_text.setText(text)
        return

    def export_txt(self):
        file_dialog = QFileDialog()
        file_name, _ = file_dialog.getSaveFileName(None, "Save File", "", "Text Files(*.txt)")
        if file_name:
            with open(file_name, "w") as file:
                file.write(self.output_text.toPlainText())
        return


if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
    app.setStyleSheet(qdarkstyle.load_stylesheet(qt_api='pyqt5'))
    w = MainWindow()
    w.setWindowTitle('单词链统计')
    w.show()
    sys.exit(app.exec())
