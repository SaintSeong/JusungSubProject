#이 코드는 PyQt5를 사용하여 동적으로 버튼과 트리뷰를 생성하는 예제입니다. config.ini 파일에서 버튼의 개수, 폴더 이름 및 루트 경로를 읽어옵니다.\
#좌측에는 버튼들이 수직으로 정렬된 레이아웃이 있으며, 버튼 사이에는 고정된 간격이 적용됩니다.
#우측에는 TreeView가 있는 레이아웃이 있으며, 버튼을 클릭하면 해당 버튼에 대응하는 폴더의 파일 및 폴더 구조를 표시합니다.
#버튼을 더블 클릭하면 TreeView가 업데이트되고, 단일 클릭은 "hello"를 출력합니다.

import configparser
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QTreeView, QFileSystemModel, QSplitter, QSizePolicy
from PyQt5.QtCore import QTimer

app = QApplication([])

# INI 파일 로드
config = configparser.ConfigParser()
config.read('config.ini')

# 버튼 개수 가져오기
count = config.getint('Count', 'Count')

# 윈도우 생성
window = QWidget()
window.setWindowTitle("Dynamic Buttons")
main_layout = QVBoxLayout(window)

# 좌측 버튼 레이아웃 생성
button_layout = QVBoxLayout()
button_layout.setContentsMargins(0, 0, 0, 0)  # 레이아웃의 마진을 0으로 설정
button_layout.setSpacing(0)  # 레이아웃 내의 요소 사이의 간격을 0으로 설정

left_widget = QWidget()  # 좌측 위젯
left_widget.setLayout(button_layout)
left_widget.setFixedSize(200, 100)
left_widget.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Expanding)  # 크기 정책을 고정으로 설정

# 우측 TreeView 레이아웃 생성
tree_layout = QVBoxLayout()
right_widget = QWidget()  # 우측 위젯
right_widget.setLayout(tree_layout)

# 버튼에 대응하는 QTreeView를 저장할 변수
tree_views = {}

# 버튼 클릭 시 TreeView 업데이트 함수
def update_tree_view():
    sender = app.sender()  # 현재 클릭된 버튼을 가져옴
    folder_root = sender.folder_root

    # 기존의 QTreeView를 제거
    for button, tree_view in tree_views.items():
        tree_layout.removeWidget(tree_view)
        tree_view.setParent(None)

    model = QFileSystemModel()
    model.setRootPath(folder_root)

    tree_view = QTreeView()
    tree_view.setFixedWidth(500)
    tree_view.setFixedHeight(300)
    tree_view.setModel(model)
    tree_view.setRootIndex(model.index(folder_root))

    tree_layout.addWidget(tree_view)
    tree_views[sender] = tree_view


def button_double_clicked():
    update_tree_view()

def button_single_click():
    print("hello")

# 버튼 생성 및 추가
for i in range(count):
    section_name = str(i)
    folder_name = config.get(section_name, 'FolderName')
    folder_root = config.get(section_name, 'FolderRoot')

    button = QPushButton(folder_name)
    button_layout.addWidget(button)

    # 버튼 사이의 간격을 위한 빈 위젯 추가
    if i < count - 1:
        spacer = QWidget()
        spacer.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        spacer.setFixedHeight(5)  # 간격의 높이를 5로 설정
        button_layout.addWidget(spacer)

    # 버튼 객체에 folder_root 속성 추가
    button.folder_root = folder_root

     # 더블 클릭 이벤트를 처리하기 위한 변수와 타이머 생성
    double_click_timer = QTimer()
    double_click_timer.setSingleShot(True)
    
    def button_clicked():
        if double_click_timer.isActive():
            # 더블 클릭 이벤트 처리
            double_click_timer.stop()
            update_tree_view()
       
        else:
            # 단일 클릭 이벤트 처리
            double_click_timer.start(2000)
            button_single_click()

    button.clicked.connect(button_clicked)


# 좌우 레이아웃을 갖는 QSplitter 생성
splitter = QSplitter()
splitter.addWidget(left_widget)
splitter.addWidget(right_widget)
main_layout.addWidget(splitter)

window.show()
app.exec()