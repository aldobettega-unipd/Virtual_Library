#include "SearchWidget.h"
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>

SearchWidget::SearchWidget(QWidget* parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void SearchWidget::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // barra di ricerca
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("CERCA UNA RISORSA");
    mainLayout->addWidget(searchBar);

    searchButton = new QPushButton(" Cerca", this);
    resetButton = new QPushButton("↻ Reset", this);
    mainLayout->addWidget(searchButton);
    mainLayout->addWidget(resetButton);

    QGroupBox* filterGroup = new QGroupBox("Filtri", this);
    formLayout = new QFormLayout(filterGroup);

    // filtri anno
    QWidget* annoWidget = new QWidget(filterGroup);
    QVBoxLayout* annoLayout = new QVBoxLayout(annoWidget);
    annoLayout->setSpacing(2);
    annoLayout->setContentsMargins(0, 0, 0, 0);

    box2000oggi = new QCheckBox("2000 - oggi", annoWidget);
    box1900 = new QCheckBox("1900 - 1999", annoWidget);
    box1800 = new QCheckBox("1800 - 1899", annoWidget);
    box1700 = new QCheckBox("1700 - 1799", annoWidget);
    boxPrima1700 = new QCheckBox("fino al 1700", annoWidget);

    annoLayout->addWidget(box2000oggi);
    annoLayout->addWidget(box1900);
    annoLayout->addWidget(box1800);
    annoLayout->addWidget(box1700);
    annoLayout->addWidget(boxPrima1700);

    formLayout->addRow("Anno di pubblicazione:", annoWidget);

    // Filtro autore
    linguaEdit = new QLineEdit(filterGroup);
    linguaEdit->setPlaceholderText("Inserisci lingua...");
    formLayout->addRow("Lingua:", linguaEdit);

    // Filtro genere
    genereEdit = new QLineEdit(filterGroup);
    genereEdit->setPlaceholderText("Inserisci genere...");
    formLayout->addRow("Genere:", genereEdit);

    // Filtro disponibilità
    disponibileCheck = new QCheckBox("Solo disponibili", filterGroup);
    formLayout->addRow("Disponibilità:", disponibileCheck);

    filterGroup->setLayout(formLayout);
    mainLayout->addWidget(filterGroup);

    // Imposta margini e spaziatura
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(10);
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(10, 15, 10, 15);
}

void SearchWidget::setupConnections() {
    connect(searchButton, &QPushButton::clicked, this, &SearchWidget::onSearchButtonClicked);

    connect(resetButton, &QPushButton::clicked, this, &SearchWidget::onResetButtonClicked);

    connect(searchBar, &QLineEdit::returnPressed, this, &SearchWidget::onSearchButtonClicked);
}

void SearchWidget::onSearchButtonClicked() {
    QString searchText = searchBar->text();
    QMap<QString, QVariant> filters;
    if (!searchText.isEmpty()) {
        filters["searchText"] = searchText;
    }

    QStringList anniSelezionati;
    if (box2000oggi->isChecked()) anniSelezionati.append("2000-oggi");
    if (box1900->isChecked()) anniSelezionati.append("1900-1999");
    if (box1800->isChecked()) anniSelezionati.append("1800-1899");
    if (box1700->isChecked()) anniSelezionati.append("1700-1799");
    if (boxPrima1700->isChecked()) anniSelezionati.append("prima-1700");

    // Se almeno un anno è selezionato, applica il filtro
    if (!anniSelezionati.isEmpty()) {
        filters["anni"] = anniSelezionati;
    }

    if (!linguaEdit->text().trimmed().isEmpty()) {
        filters["lingua"] = linguaEdit->text().trimmed();
    }

    if (!genereEdit->text().trimmed().isEmpty()) {
        filters["genere"] = genereEdit->text().trimmed();
    }

    if (disponibileCheck->isChecked()) {
        filters["solo_disponibili"] = true;
    }

    emit filtersChanged(filters);
}

void SearchWidget::onResetButtonClicked() {
    // Reset tutti i campi
    searchBar->clear();
    box2000oggi->setChecked(false);
    box1900->setChecked(false);
    box1800->setChecked(false);
    box1700->setChecked(false);
    boxPrima1700->setChecked(false);
    linguaEdit->clear();
    genereEdit->clear();
    disponibileCheck->setChecked(false);

    // Emetti segnali per resettare la gallery
    emit searchTextChanged("");
    emit filtersChanged(QMap<QString, QVariant>());
}










