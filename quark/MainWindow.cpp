#include "MainWindow.h"
#include "QuarkWindow.h"
#include "QuarkWindowEvent.h"
#include "QuarkString.h"

#include <qsplitter.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qstatusbar.h>
#include <qicon.h>
#include <qtabwidget.h>
#include <qtreewidget.h>
#include <qwidget.h>
#include <qtoolbutton.h>
#include <qheaderview.h>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <qmimedata.h>
#include <qlabel.h>
#include <qmenubar.h>
#include <qmenu.h>
#include <qaction.h>
#include <qtimer.h>
#include <qdesktopservices.h>
#include <qfiledialog.h>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSpacerItem>

#include <iostream>
#include <fstream>
#include <vector>

#include <qdebug.h>


qe::edit::MainWindow::MainWindow()
{
    setAcceptDrops(true);
    InitUI();

    fps_timer_ = std::make_shared<QTimer>();
    connect(fps_timer_.get(), SIGNAL(timeout()), this, SLOT(UpdateFps()));
    fps_timer_->start();
}

qe::edit::MainWindow::~MainWindow()
{
    ClearUI();
}

void qe::edit::MainWindow::InitUI()
{
    InitWindowBase();
    InitLayout();
}

void qe::edit::MainWindow::NewProjectAction()
{
	std::cout << "new project action \n";
}

void qe::edit::MainWindow::OpenProjectAction()
{
	std::cout << "open project action \n";
}

void qe::edit::MainWindow::SaveProjectAction()
{
	std::cout << "save project action \n";
}

void qe::edit::MainWindow::NewSceneAction()
{
	std::cout << "new scene action \n";
}

void qe::edit::MainWindow::OpenSceneAction()
{
	project_file_ = QFileDialog::getOpenFileName(this,
		tr("Open Project"), "D:/media/models/maya/", tr("Project Files (*.fbx *.obj)"));

	if (project_file_.isEmpty()) return;

	quark_window_->OpenScene(project_file_.toStdString());
}

void qe::edit::MainWindow::SaveSceneAction()
{
	std::cout << "save scene action \n";
}

void qe::edit::MainWindow::ExitAction()
{
	this->close();
}

void qe::edit::MainWindow::QuarkManualAction()
{
	QDesktopServices::openUrl(QUrl("D:/project/quark_engine/doc/html/index.html"));
}

void qe::edit::MainWindow::UpdateFps()
{
    this->statusBar()->showMessage(QString::number(quark_window_->get_fps()) + " fps");
}

void qe::edit::MainWindow::dragEnterEvent(QDragEnterEvent * event)
{
    std::cout << "dragEnterEvent \n";

    event->acceptProposedAction();
}

void qe::edit::MainWindow::dropEvent(QDropEvent * event)
{
    std::cout << "dropEvent \n";

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
   
    qDebug() << "file Name " << fileName;
}

void qe::edit::MainWindow::InitWindowBase()
{
    InitIcon();
    InitWindowName();
    InitWindowSize();
}

void qe::edit::MainWindow::InitLayout()
{
    InitMenuBar();

    InitSplitterPolicy();

    InitSceneTreeUI();
    InitSceneUI();
    InitSceneUILayout();

    InitContentUI();

    InitLeftMainUILayout();

    InitPropertyUI();
    InitMainUILayout();

    InitStatusBar();
}

void qe::edit::MainWindow::InitIcon()
{
    this->setWindowIcon(QIcon("D:/project/quark_engine/media/image/quark.png"));
}

void qe::edit::MainWindow::InitWindowName()
{
    this->setWindowTitle("quark " + QString::number(version_, 'f', 4));
}

void qe::edit::MainWindow::InitWindowSize()
{
    QRect screen_rect = QApplication::desktop()->screenGeometry();

    QRect window_rect;
    window_rect.setX(0);
    window_rect.setY(WindowParameter::window_tile_height);
    window_rect.setWidth(screen_rect.width() - 4);
    window_rect.setHeight(screen_rect.height() - WindowParameter::windows_taskbar_height);

    this->setGeometry(window_rect);

}

void qe::edit::MainWindow::InitMenuBar()
{
    auto menu_bar = this->menuBar();

	//File
	auto file_menu = std::make_shared<QMenu>("File");

	auto new_project_action = file_menu->addAction("New Project");
	auto open_project_action = file_menu->addAction("Open Project");
	auto save_project_action = file_menu->addAction("Save Project");

	file_menu->addSeparator();

	auto new_scene_action = file_menu->addAction("New Scene");
	auto open_scene_action = file_menu->addAction("Open Scene");
	auto save_scene_action = file_menu->addAction("Save Scenes");

	file_menu->addSeparator();

	auto build_settings_action = file_menu->addAction("Build Settings");
	auto exit_action = file_menu->addAction("Exit");


	//Eidt
	auto edit_menu = std::make_shared<QMenu>("Edit");
	auto proejct_setting_menu = edit_menu->addMenu("Project Settings");
	auto quality_action = proejct_setting_menu->addAction("Quality");


	//Assets
	auto assets_menu = std::make_shared<QMenu>("Assets");
	auto refresh_action = assets_menu->addAction("Refresh");


	//QuarkObject
	auto quark_object_menu = std::make_shared<QMenu>("Quark Object");
	auto create_empty_action = quark_object_menu->addAction("Create Empty");

	quark_object_menu->addSeparator();

	auto light_menu = quark_object_menu->addMenu("Light");
	auto direction_light_action = light_menu->addAction("Direction Light");
	auto point_light_action = light_menu->addAction("Point Light");
	auto spot_light_action = light_menu->addAction("Spot Light");
	auto area_light_action = light_menu->addAction("Area Light");

	quark_object_menu->addSeparator();

	auto camera_action = quark_object_menu->addAction("Camera");


	//Component
	auto component_menu = std::make_shared<QMenu>("Component");
	auto mesh_menu = component_menu->addMenu("Mesh");
	auto mesh_renderer_action = mesh_menu->addAction("Mesh Renderer");


	//Window
	auto window_menu = std::make_shared<QMenu>("Window");
	auto asset_store_action = window_menu->addAction("Asset Store");
	auto profiler_action = window_menu->addAction("Profiler");


	//Help
	auto help_menu = std::make_shared<QMenu>("Help");
	auto about_quark_action = help_menu->addAction("About Quark");

	help_menu->addSeparator();

	auto manage_license_action = help_menu->addAction("Manage license");
	auto quark_manual_action = help_menu->addAction("Quark Manual");

	help_menu->addSeparator();

	auto check_for_updates_action = help_menu->addAction("Check for Updates");
	auto report_a_bug_action = help_menu->addAction("Report a Bug");


	//add menu to menu bar
	menu_bar->addMenu(file_menu.get());
	menu_bar->addMenu(edit_menu.get());
	menu_bar->addMenu(assets_menu.get());
	menu_bar->addMenu(quark_object_menu.get());
	menu_bar->addMenu(component_menu.get());
	menu_bar->addMenu(window_menu.get());
	menu_bar->addMenu(help_menu.get());

	//push menu to menu list
	menus_.push_back(file_menu);
	menus_.push_back(edit_menu);
	menus_.push_back(assets_menu);
	menus_.push_back(quark_object_menu);
	menus_.push_back(component_menu);
	menus_.push_back(window_menu);
	menus_.push_back(help_menu);

	connect(new_project_action, SIGNAL(triggered()), this, SLOT(NewProjectAction()));
	connect(open_project_action, SIGNAL(triggered()), this, SLOT(OpenProjectAction()));
	connect(save_project_action, SIGNAL(triggered()), this, SLOT(SaveProjectAction()));

	connect(new_scene_action, SIGNAL(triggered()), this, SLOT(NewSceneAction()));
	connect(open_scene_action, SIGNAL(triggered()), this, SLOT(OpenSceneAction()));
	connect(save_scene_action, SIGNAL(triggered()), this, SLOT(SaveSceneAction()));

	connect(exit_action, SIGNAL(triggered()), this, SLOT(ExitAction()));

	connect(quark_manual_action, SIGNAL(triggered()), this, SLOT(QuarkManualAction()));

}

void qe::edit::MainWindow::InitStatusBar()
{
    this->statusBar()->showMessage(tr("Hello world!  i'm quark engine! ^v^"));
}

void qe::edit::MainWindow::InitSplitterPolicy()
{
    // fixed widget expand bug!
    tab_splitter_policy_ = DBG_NEW QSizePolicy();
    tab_splitter_policy_->setHorizontalPolicy(QSizePolicy::Ignored);
    tab_splitter_policy_->setVerticalPolicy(QSizePolicy::Ignored);
    tab_splitter_policy_->setHorizontalStretch(0);
    tab_splitter_policy_->setVerticalStretch(0);

    button_policy_ = DBG_NEW QSizePolicy();
    button_policy_->setHorizontalPolicy(QSizePolicy::Expanding);
    button_policy_->setVerticalPolicy(QSizePolicy::Expanding);
    button_policy_->setHorizontalStretch(0);
    button_policy_->setVerticalStretch(0);
}

void qe::edit::MainWindow::InitSceneTreeUI()
{
    scene_tree_tab_widget_ = DBG_NEW QTabWidget();

    scene_tree_tab_ = DBG_NEW QWidget();
    scene_tree_tab_widget_->addTab(scene_tree_tab_, "scene tree");
    scene_tree_tab_widget_->setTabShape(QTabWidget::Triangular);
}

void qe::edit::MainWindow::InitSceneUI()
{
    scene_widget_ = DBG_NEW QWidget();
    scene_tab_widget_ = DBG_NEW QTabWidget();
    scene_tab_ = DBG_NEW QWidget();

    play_button_ = DBG_NEW QToolButton();
    pause_button_ = DBG_NEW QToolButton();
    next_frame_button_ = DBG_NEW QToolButton();

    scene_button_layout_ = DBG_NEW QHBoxLayout(); 
    secne_widget_layout_ = DBG_NEW QVBoxLayout();

    quark_window_event_ = DBG_NEW QuarkWindowEvent();

    quark_window_ = DBG_NEW QuarkWindow();
    quark_window_->installEventFilter(quark_window_event_);

    quark_window_->Init();
    vulkan_window_containter_ = QWidget::createWindowContainer(quark_window_);

    scene_layout_ = DBG_NEW QVBoxLayout();

    scene_tab_widget_->addTab(scene_tab_, "scene");
    scene_tab_widget_->setTabShape(QTabWidget::Triangular);

    play_button_->setText("play");
    pause_button_->setText("pause");
    next_frame_button_->setText("next");

    play_button_->setSizePolicy(*button_policy_);
    pause_button_->setSizePolicy(*button_policy_);
    next_frame_button_->setSizePolicy(*button_policy_);

    scene_button_layout_->addStretch(650);

    scene_button_layout_->addWidget(play_button_);
    scene_button_layout_->addWidget(pause_button_);
    scene_button_layout_->addWidget(next_frame_button_);

    scene_button_layout_->addStretch(650);

    scene_button_layout_->setStretch(0, 8);
    scene_button_layout_->setStretch(1, 1);
    scene_button_layout_->setStretch(2, 1);
    scene_button_layout_->setStretch(3, 1);
    scene_button_layout_->setStretch(4, 8);

    empty_widget_ = DBG_NEW QWidget();
    scene_layout_->addWidget(empty_widget_);
    scene_layout_->addWidget(vulkan_window_containter_);

    scene_layout_->setStretch(0, 1);
    scene_layout_->setStretch(1, 25);

    scene_tab_->setLayout(scene_layout_);

    secne_widget_layout_->addLayout(scene_button_layout_);
    secne_widget_layout_->addWidget(scene_tab_widget_);

    secne_widget_layout_->setStretch(0, 1);
    secne_widget_layout_->setStretch(1, 25);

    scene_widget_->setLayout(secne_widget_layout_);

}

void qe::edit::MainWindow::InitContentUI()
{
    content_tab_widget_ = DBG_NEW QTabWidget();

    content_tab_ = DBG_NEW QWidget();
    content_tab_widget_->addTab(content_tab_, "content");
    content_tab_widget_->setTabShape(QTabWidget::Triangular);

    InitInsideContentUILayout();

    content_layout_ = DBG_NEW QHBoxLayout();

    content_layout_->addWidget(content_tab_splitter_);

    content_tab_->setLayout(content_layout_);

}

void qe::edit::MainWindow::InitPropertyUI()
{
    property_tab_widget_ = DBG_NEW QTabWidget();

    property_tab_ = DBG_NEW QWidget();

    property_tab_widget_->addTab(property_tab_, "property");
    property_tab_widget_->setTabShape(QTabWidget::Triangular);

    property_tab_widget_->setAcceptDrops(false);
    property_tab_->setAcceptDrops(false);
}

void qe::edit::MainWindow::InitSceneUILayout()
{
    scene_splitter_ = DBG_NEW QSplitter();
    scene_splitter_->setOrientation(Qt::Horizontal);
    scene_splitter_->setSizePolicy(*tab_splitter_policy_);

    scene_splitter_->addWidget(scene_tree_tab_widget_);
    scene_splitter_->addWidget(scene_widget_);

    scene_splitter_->setStretchFactor(0, 1);
    scene_splitter_->setStretchFactor(1, 4);
}

void qe::edit::MainWindow::InitInsideContentUILayout()
{
    content_tab_splitter_ = DBG_NEW QSplitter();
    content_tab_splitter_->setOrientation(Qt::Horizontal);
    content_tab_splitter_->setSizePolicy(*tab_splitter_policy_);

    content_tree_widget_ = DBG_NEW QTreeWidget();
    content_detail_tree_widget_ = DBG_NEW QTreeWidget();

    content_tree_widget_->header()->setVisible(false);
    content_detail_tree_widget_->header()->setVisible(false);

    content_tab_splitter_->addWidget(content_tree_widget_);
    content_tab_splitter_->addWidget(content_detail_tree_widget_);

    content_tab_splitter_->setStretchFactor(0, 10);
    content_tab_splitter_->setStretchFactor(1, 76);
}

void qe::edit::MainWindow::InitLeftMainUILayout()
{
    left_main_splitter_ = DBG_NEW QSplitter();
    left_main_splitter_->setOrientation(Qt::Vertical);
    left_main_splitter_->setSizePolicy(*tab_splitter_policy_);

    left_main_splitter_->addWidget(scene_splitter_);
    left_main_splitter_->addWidget(content_tab_widget_);

    left_main_splitter_->setStretchFactor(0, 2);
    left_main_splitter_->setStretchFactor(1, 1);
}

void qe::edit::MainWindow::InitMainUILayout()
{
    center_widget_ = DBG_NEW QWidget(this);
    main_layout_ = DBG_NEW QHBoxLayout(center_widget_);

    main_splitter_ = DBG_NEW QSplitter();
    main_splitter_->setOrientation(Qt::Horizontal);
    main_splitter_->setSizePolicy(*tab_splitter_policy_);

    main_splitter_->addWidget(left_main_splitter_);
    main_splitter_->addWidget(property_tab_widget_);

    main_layout_->addWidget(main_splitter_);

    main_splitter_->setStretchFactor(0, 2);
    main_splitter_->setStretchFactor(1, 1);

    this->setCentralWidget(center_widget_);
    center_widget_->setLayout(main_layout_);
}



void qe::edit::MainWindow::ClearUI()
{
    delete tab_splitter_policy_;
    delete button_policy_;

    delete quark_window_event_;
}

