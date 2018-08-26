#pragma once

#include <qmainwindow.h>

#include "EditObject.h"

class QSplitter;
class QTabWidget;
class QTreeWidget;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class QSpacerItem;
class QDragEnterEvent;
class QDropEvent;
class QMenu;
class QAction;


namespace qe {
    namespace edit {
        class QuarkWindow;

        class MainWindow : public QMainWindow , public EditObject 
        {
            Q_OBJECT
        public:
            explicit MainWindow();
            ~MainWindow();

            void InitUI();

        public slots:
            void UpdateFps();

            void NewProjectAction();
            void OpenProjectAction();
            void SaveProjectAction();

            void NewSceneAction();
            void OpenSceneAction();
            void SaveSceneAction();

            void ExitAction();

            void QuarkManualAction();


        protected:
            void dragEnterEvent(QDragEnterEvent *event) override;
            void dropEvent(QDropEvent *event) override;

        private:
            void InitWindowBase();
            void InitLayout();

            void InitIcon();
            void InitWindowName();
            void InitWindowSize();

            void InitMenuBar();
            void InitStatusBar();

            void InitSplitterPolicy();

            void InitSceneTreeUI();
            void InitSceneUI();
            void InitSceneUILayout();

            void InitContentUI();
            void InitInsideContentUILayout();

            void InitLeftMainUILayout();

            void InitPropertyUI();
            void InitMainUILayout();

            void ClearUI();


        private:
            const double version_ = 1.0000;

            const struct WindowParameter
            {
                static const int window_tile_height = 25;
                static const int windows_taskbar_height = 70;
            };

            QSplitter *main_splitter_;
            QSplitter *left_main_splitter_;
            QSplitter *scene_splitter_;
            QSplitter *content_tab_splitter_;

            QTabWidget *scene_tree_tab_widget_;
            QTabWidget *scene_tab_widget_;
            QTabWidget *content_tab_widget_;
            QTabWidget *property_tab_widget_;

            QWidget *center_widget_;
            QWidget *scene_tree_tab_;
            QWidget *scene_tab_;
            QWidget *content_tab_;
            QWidget *property_tab_;
            QWidget *vulkan_window_containter_;
            QWidget *empty_widget_;
            QWidget *scene_widget_;

            QTreeWidget *content_tree_widget_;
            QTreeWidget *content_detail_tree_widget_;

            QHBoxLayout *main_layout_;
            QHBoxLayout *content_layout_;
            QHBoxLayout *scene_button_layout_;
            QVBoxLayout *scene_layout_;
            QVBoxLayout *secne_widget_layout_;

            QSizePolicy *tab_splitter_policy_;
            QSizePolicy *button_policy_;

            QuarkWindow *quark_window_;

            QToolButton *play_button_;
            QToolButton *pause_button_;
            QToolButton *next_frame_button_;

            std::shared_ptr<QTimer> fps_timer_;

            std::vector<std::shared_ptr<QMenu>> menus_;

            QString scene_file_;
            QString doc_path_;
            QString window_icon_;

            // after release layout ,  that inside QSpacerItem will auto release
        };
    }
}


