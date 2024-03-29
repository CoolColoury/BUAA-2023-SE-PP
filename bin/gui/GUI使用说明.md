# GUI使用说明文档

[toc]

## GUI使用说明

### GUI打开

打开`/dist/main_window/main_window.exe`文件即可。

<img src="./assets/3.png" alt="image-20230318165836881" style="zoom:50%;" />

1. 左上角为控制模块。分别对应着-n, -w, -c
2. 左下角对应的是输入模块。支持输入文本或导入文件。点击清空则会清除输入文本。点击求解则会求解当前配置下的输入文本。
3. 右方对应的是导出文本。求解后的文本会输出到右方。可以点击导出文本文件输出成txt文件。

## GUI设计说明GUI所用技术

我们构建GUI版本应用所使用的编程语言为Python，使用的包如下：

*   `PyQt5-Qt5 5.15.4`
*   `PyQt5-sip 12.11.0`
*   `PyQt5-stubs 5.15.6.0`

打包所用的插件为`pyinstaller`。

### 11.2 设计风格

我们使用的是`qdarkstyle`作为GUI的主题。

<img src="./assets/3.png" alt="image-20230318165836881" style="zoom:50%;" />

<img src="./assets/2.png" alt="image-20230318165814614" style="zoom:50%;" />

* 控制板块：左上方为控制板块。其提供三种模式的对应。

    *   单词链数量：“-n”
    *   最长单词链：“-w”
    *   字母数最多：“-c”

    其中，-n不支持其他参数，-w和-c支持其他4种参数限制，提供给用户的输入全部为选择，因此不会有控制模块的异常读入。

* 输入板块：左下方为输入板块。并提供了三个按钮，分别对应了三个功能。

* 输出板块：右方为输出板块。并提供了导出文件的按钮。

* 运行时间窗口：每次正确求解后都会弹出运行时间窗口。

    <img src="./assets/8.png" alt="f84b34916f9bee6f8760b0d2fb05c4c" style="zoom:50%;" />

* 运行异常窗口：每次求解时出现异常都会弹出异常窗口，并得到相关异常信息。

    <img src="./assets/9.png" alt="694a6ebf60d52c9b9ad3d915562dd94" style="zoom:50%;" />

### 11.3 代码设计

1. UI部分。我们采用QtDesigner的图形化设计界面得到ui的部分代码。生成如下：

    ```python
    # Form implementation generated from reading ui file 'main.ui'
    #
    # Created by: PyQt5 UI code generator 5.15.4
    #
    # WARNING: Any manual changes made to this file will be lost when pyuic5 is
    # run again.  Do not edit this file unless you know what you are doing.
    
    
    from PyQt5 import QtCore, QtGui, QtWidgets
    
    
    class Ui_MainWindow(object):
        def setupUi(self, MainWindow):
            MainWindow.setObjectName("MainWindow")
            MainWindow.resize(781, 540)
            MainWindow.setMinimumSize(QtCore.QSize(781, 540))
            MainWindow.setMaximumSize(QtCore.QSize(915, 672))
            self.centralwidget = QtWidgets.QWidget(MainWindow)
            self.centralwidget.setObjectName("centralwidget")
            self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
            self.gridLayout.setObjectName("gridLayout")
            # ...
            # ...
    ```

    控制模块采用`QTabWidget`搭建，输入输出模块采用`QPushButton`和`QTextEdit`组建搭建。整体布局采用栅格布局，同时辅以部分区域的`QVBoxLayout`和`QHBoxLayout`，并采用`Spacer`支持拉伸。

2. 读入dll库：采用python自带的ctypes库进行处理。

    ```python
    from ctypes import cdll, c_char_p, c_int, c_char, c_bool
    
    try:
        core_dll = cdll.LoadLibrary(".\\dll\\core.dll")
    except Exception as e:
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Critical)
        msgBox.setText(f'运行时出现如下异常: {e}')
        msgBox.setWindowTitle('Error')
        msgBox.exec_()
    ```

3. 单词读入函数：支持从输入框中读入文本，并解析成单词形式。（注：这一部分只提取出单词，没有进行预处理。对于单词的处理在core模块中完成。）

    ```python
    def read_words(input_text):
        result = []
        word = ""
        for c in input_text:
            if c.isalpha():
                word += c
            elif word != "":
                result.append(word)
                word = ""
        if word != "":
            result.append(word)
        return result
    ```

4. 核心界面类`MainWindow`：

    ```python
    class MainWindow(QMainWindow, Ui_MainWindow):
            
        def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)     
        self.import_txt_button.clicked.connect(self.import_txt)
        self.clear_button.clicked.connect(self.clear)
        self.solve_button.clicked.connect(self.solve)
        self.export_txt_button.clicked.connect(self.export_txt)
    ```

    以上是构造函数。继承自`QMainWindow`和`Ui_MainWindow`。通过调用`setupUi`方法设置相关ui。

    各个按钮与事件函数进行链接`connect`。

    * `import_txt`函数的目的是从文件管理器中导入txt数据，`export_txt`为导出txt文件。

        ```python
        def import_txt(self):
            file_dialog = QFileDialog()
            file_name, _ = file_dialog.getOpenFileName(None, "Select File", "", "Text Files(*.txt)")
            if file_name:
                with open(file_name, 'r') as file:
                    self.input_text.setText(file.read())
            return
        
        def export_txt(self):
            file_dialog = QFileDialog()
            file_name, _ = file_dialog.getSaveFileName(None, "Save File", "", "Text Files(*.txt)")
            if file_name:
                with open(file_name, "w") as file:
                    file.write(self.output_text.toPlainText())
            return
        ```

    * `clear`函数的目的是同时清空输入和输出。

        ```python
        def clear(self):
            self.input_text.clear()
            self.output_text.clear()
            return
        ```

    * `solve`函数为核心函数。

        ```python
        def solve(self):
            # 预处理+转换成cpp的type
            success = True
            start_time = time.time()
            index = self.tabWidget.currentIndex()
            words = read_words(self.input_text.toPlainText())
            len_w = len(words)
            c_words = (c_char_p * len_w)()
            for i in range(len_w):
                c_words[i] = words[i].encode('utf-8')
            c_len = c_int(len(words))
            result = (c_char_p * 20000)()
            
            # -n处理
            if index == 0:
                ans = 0
                try:
                    ans = core_dll.gen_chains_all(c_words, c_len, result)
                except Exception as e:
                    # ...
                    # 弹出异常框
                results = [result[i].decode('utf-8') for i in range(ans)]
                # ...
                # 设置输出
            
            # -w处理
            else if index == 1:
                h = self.w_h_box.currentText()
                # ...
                # 预处理
                try:
                    ans = core_dll.gen_chain_word(c_words, c_len, result, c_h, c_t, c_n_h, c_r)
                except Exception as e:
                    # ...
                	# 弹出异常框
                results = [result[i].decode('utf-8') for i in range(ans)]
                # ...
                # 设置输出
                
            # -c处理
            elif index == 2:
                h = self.c_h_box.currentText()
                # ...
                # 预处理
                try:
                    ans = core_dll.gen_chain_char(c_words, c_len, result, c_h, c_t, c_n_h, c_r)
                except Exception as e:
                    # ...
                    # 弹出异常框
                results = [result[i].decode('utf-8') for i in range(ans)]
                # ...
                # 设置输出
                
            # 记录时间并弹出窗口
            run_time = time.time() - start_time
            if success:
                QMessageBox.information(None, "运行时间", f"{run_time:.2f} seconds")
            return
        ```

5. 主程序：

    ```python
    if __name__ == "__main__":
    
        app = QApplication(sys.argv)
        app.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
        app.setStyleSheet(qdarkstyle.load_stylesheet(qt_api='pyqt5'))
        w = MainWindow()
        w.setWindowTitle('单词链统计')
        w.show()
    
        sys.exit(app.exec())
    ```

## 12 界面模块与计算模块的对接

### 12.1 前后端对接

通过采用python自带的ctypes库导入dll库，并直接使用dll库的函数。

导入dll库的代码为：

```python
from ctypes import cdll, c_char_p, c_int, c_char, c_bool

try:
    core_dll = cdll.LoadLibrary(".\\dll\\core.dll")
except Exception as e:
    msgBox = QMessageBox()
    msgBox.setIcon(QMessageBox.Critical)
    msgBox.setText(f'运行时出现如下异常: {e}')
    msgBox.setWindowTitle('Error')
    msgBox.exec_()
```

函数直接调用即可。

如：`ans = core_dll.gen_chains_all(c_words, c_len, result)`

我们通过visual studio 2019导出dll。相关的导出模块定义如下：

```def
LIBRARY Wordlist
EXPORTS
	gen_chains_all
	gen_chain_word
	gen_chain_char
	get_error_message
```

对应的接口函数：

```cpp
int gen_chains_all(const char* words[], int len, char* result[]);
int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop);
int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop);

char* get_error_message();
```

