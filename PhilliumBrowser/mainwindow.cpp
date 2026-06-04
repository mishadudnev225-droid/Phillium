#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWindow>
#include <QSurface>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 1. Создаем центральный виджет-контейнер
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 2. Создаем вертикальный Layout (компоновщик)
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Отступы окна в 0, чтобы рендер прижимался к краям
    mainLayout->setSpacing(0);                  // Расстояние между строкой поиска и рендером

    // 3. Создаем строку поиска
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Введите URL или поисковый запрос...");
    // Можно задать фиксированную высоту или отступы для красоты внутри строки
    searchBar->setStyleSheet("QLineEdit { padding: 6px; font-size: 14px; }");

    // 4. Создаем нативное окно для Vulkan
    QWindow *vulkanWindow = new QWindow();
    vulkanWindow->setSurfaceType(QSurface::VulkanSurface);

    // Встраиваем QWindow внутрь QtWidgets через специальный контейнер
    // Сохраняем его в переменную renderWidget, которая объявлена у вас в mainwindow.h
    renderWidget = QWidget::createWindowContainer(vulkanWindow, this);

    // 5. Собираем интерфейс строго по порядку: СНАЧАЛА поиск, ПОТОМ рендер
    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(renderWidget);

    // Указываем пропорции: строка поиска не растягивается (0), а Vulkan-виджет забирает всё место (1)
    mainLayout->setStretchFactor(searchBar, 0);
    mainLayout->setStretchFactor(renderWidget, 1);

    // 6. Получаем дескриптор окна для Vulkan-движка
    WId nativeHandle = vulkanWindow->winId();

    // ПЕРЕДАЧА В ВАШ ДВИЖОК:
    // Здесь вы должны вызвать инициализацию вашего Vulkan-движка рендера,
    // передав туда nativeHandle. Например:
    // myVulkanEngine->initSurface(nativeHandle);

    // Задаем стартовый размер окна браузера
    resize(1024, 768);
}

MainWindow::~MainWindow() {
    // Все дочерние объекты Qt удалит автоматически сама.
}
