#include "SearchWidget.h"
#include <QLabel>
#include <QCheckBox>

SearchWidget::SearchWidget(QWidget* parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void SearchWidget::setupUI() {
    layout = new QVBoxLayout(this);

    // barra di ricerca
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("CERCA UNA RISORSA");
    layout->addWidget(searchBar);

    //filtri
    filterBox = new QWidget(this);
    QVBoxLayout* filterLayout = new QVBoxLayout(filterBox);

    // filtri anno
    QLabel* label_anno = new QLabel("Anno di pubblicazione", filterBox);
    box2000oggi = new QCheckBox("2000 - oggi", filterBox);
    box1900 = new QCheckBox("1900 - 1999", filterBox);
    box1800 = new QCheckBox("1800 - 1899", filterBox);
    box1700 = new QCheckBox("1700 - 1799", filterBox);
    boxPrima1700 = new QCheckBox("fino al 1700", filterBox);

    // filtri autore e genere
    QLabel* label_autore = new QLabel("Autore", filterBox);
    autoreEdit = new QLineEdit(filterBox);
    autoreEdit->setPlaceholderText("Filtra per autore...");

    QLabel* label_genere = new QLabel("Genere", filterBox);
    genereEdit = new QLineEdit(filterBox);
    genereEdit->setPlaceholderText("Filtra per genere...");

    disponibileCheck = new QCheckBox("Solo disponibili", filterBox);

    filterLayout->addWidget(label_anno);
    filterLayout->addWidget(box2000oggi);
    filterLayout->addWidget(box1900);
    filterLayout->addWidget(box1800);
    filterLayout->addWidget(box1700);
    filterLayout->addWidget(boxPrima1700);
    filterLayout->addWidget(label_autore);
    filterLayout->addWidget(autoreEdit);
    filterLayout->addWidget(label_genere);
    filterLayout->addWidget(genereEdit);
    filterLayout->addWidget(disponibileCheck);


    filterBox->setLayout(filterLayout);

    layout->addWidget(filterBox);
}

void SearchWidget::setupConnections() {
    connect(searchBar, &QLineEdit::textChanged, this, &SearchWidget::onSearchTextChanged);

    connect(box2000oggi, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);
    connect(box1900, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);
    connect(box1800, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);
    connect(box1700, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);
    connect(boxPrima1700, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);

    connect(autoreEdit, &QLineEdit::textChanged, this, &SearchWidget::onFiltersChanged);
    connect(genereEdit, &QLineEdit::textChanged, this, &SearchWidget::onFiltersChanged);

    connect(disponibileCheck, &QCheckBox::stateChanged, this, &SearchWidget::onFiltersChanged);
}

void SearchWidget::onSearchTextChanged(const QString& text) {
    emit searchTextChanged(text);
}

void SearchWidget::onFiltersChanged() {
    QMap<QString, QVariant> filters;

    // filtro anno
    if (box2000oggi->isChecked()) filters["anno"] = "2000-oggi";
    else if (box1900->isChecked()) filters["anno"] = "1900-1999";
    else if (box1800->isChecked()) filters["anno"] = "1800-1899";
    else if (box1700->isChecked()) filters["anno"] = "1700-1799";
    else if (boxPrima1700->isChecked()) filters["anno"] = "prima-1700";

    // filtro autore
    if (!autoreEdit->text().isEmpty()) {
        filters["autore"] = autoreEdit->text();
    }

    // filtro genere
    if (!genereEdit->text().isEmpty()) {
        filters["genere"] = genereEdit->text();
    }

    // filtro disponibilità
    if (!disponibileCheck->isChecked()) {
        filters["disponibile"] = false;
    }

    emit filtersChanged(filters);
}










