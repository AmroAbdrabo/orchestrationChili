/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file TranslationTool.h
 * @brief Header for QML-side dynamic translation
 * @author Ayberk Özgür
 * @date 2016-08-15
 */

#ifndef TRANSLATIONTOOL_H
#define TRANSLATIONTOOL_H

#include <QtGui>

/**
 * @brief Tool to provide translation for entire app
 */
class TranslationTool : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(QVariantMap languageList READ getLanguageList WRITE setLanguageList NOTIFY languageListChanged)
    Q_PROPERTY(QString estr READ getEmptyString NOTIFY languageChanged)

public:

    /**
     * @brief Creates new translation tool and QTranslator and attaches it to this object
     */
    TranslationTool(QObject* parent = 0);

    /**
     * @brief Destroys the translation tool and the QTranslator
     */
    ~TranslationTool();

    /**
     * @brief Sets the language-translation file map
     *
     * @param newList New map from language (QString) to translation file (QString)
     */
    void setLanguageList(const QVariantMap& newList);

    /**
     * @brief Gets the language list
     *
     * @return Map from language (QString) to translation file (QString)
     */
    QVariantMap getLanguageList(){ return languageList; }

    /**
     * @brief Gets an empty string (hack to dynamically update texts in the UI)
     *
     * @return ""
     */
    QString getEmptyString(){ return ""; }

signals:

    /**
     * @brief Emitted when the language to translation file list changes
     */
    void languageListChanged();

    /**
     * @brief Emitted when language has changed
     */
    void languageChanged();

public slots:

    /**
     * @brief Chooses language
     *
     * @param language Language as provided to the translation list or "default" to uninstall translator
     */
    Q_INVOKABLE void selectLanguage(const QString& language);

private:

    QTranslator translator;   ///< Translator to be attached to the qApp
    QVariantMap languageList; ///< Language (QString) to translation file (QString) list

};

#endif
