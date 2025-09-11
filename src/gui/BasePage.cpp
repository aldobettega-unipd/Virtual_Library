#include "BasePage.h"
#include <QDebug>

BasePage::BasePage(QWidget* parent) : QWidget(parent) {
    setupCommonUI();
    setupCommonConnections();
}

void BasePage::setupCommonUI() {
    //parte principale
    mainLayout = new QVBoxLayout(this);

    //barra di menu
    setupMenuBar();

    //parte di ricerca
    QHBoxLayout* centralLayout = new QHBoxLayout;
    searchWidget = new SearchWidget(this);

    galleryWidget = new GalleryWidget(false, this);

    centralLayout->addWidget(searchWidget);
    centralLayout->addWidget(galleryWidget);
    centralLayout->setStretch(0, 1);
    centralLayout->setStretch(1, 3);

    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(centralLayout);
}

void BasePage::setupMenuBar() {
    menuBar = new QWidget(this);
    QHBoxLayout* menuLayout = new QHBoxLayout(menuBar);
    logoutButton = new QPushButton("Logout", this);
    menuLayout->addWidget(logoutButton, 0, Qt::AlignLeft);
}

void BasePage::setupCommonConnections() {
    connect(logoutButton, &QPushButton::clicked, this, &BasePage::logoutRequested);
    connect(galleryWidget, &GalleryWidget::mediaClicked, this, &BasePage::mediaClicked);

    connect(searchWidget, &SearchWidget::searchTextChanged, galleryWidget, &GalleryWidget::filterByText);
    connect(searchWidget, &SearchWidget::filtersChanged, galleryWidget, &GalleryWidget::applyFilters);

}

void BasePage::onBibliotecaUpdated(const QList<Biblioteca*>& data) {
    galleryWidget->setMediaData(data);
}
