/*
* Copyright (C) 2016 Alexey Polushkin, armijo38@yandex.ru
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* Full license: http://dimkanovikov.pro/license/GPLv3
*/

#ifndef SYNCHRONIZATIONMANAGERV2_H
#define SYNCHRONIZATIONMANAGERV2_H

#include <QObject>

class NetworkRequest;
class QXmlStreamReader;


namespace ManagementLayer
{
	/**
	 *  @brief Управляющий синхронизацией
	 */
	class SynchronizationManagerV2 : public QObject
	{
		Q_OBJECT

	public:
		explicit SynchronizationManagerV2(QObject* _parent, QWidget* _parentView);

		//
		// Методы работы с аккаунтом
		//

		/**
		 * @brief Активна ли подписка у пользователя
		 */
		bool isSubscriptionActive() const;

		/**
		 * @brief Авторизоваться на сервере, используя сохраненные логин и пароль
		 */
		void autoLogin();

		/**
		 * @brief Авторизоваться на сервере
		 */
		void login(const QString& _email, const QString& _password);

		/**
		 * @brief Регистрация на сервере
		 */
		void signUp(const QString& _email, const QString& _password);

		/**
		 * @brief Подтверждение регистрации при помощи проверочного кода
		 */
		void verify(const QString& _code);

		/**
		 * @brief Восстановление пароля
		 */
		void restorePassword(const QString& _email);

		/**
		 * @brief Закрыть авторизацию
		 */
		void logout();

		/**
		 * @brief Продлить подписку
		 */
		void renewSubscription(unsigned _duration, unsigned _type);

		/**
		 * @brief Сменить имя пользователя
		 */
		void changeUserName(const QString& _newUserName);

		/**
		 * @brief Получить информацию о подписке
		 */
		void loadSubscriptionInfo();

		/**
		 * @brief Сменить пароль
		 */
		void changePassword(const QString& _password, const QString& _newPassword);

		//
		// Методы работы с проектами
		//

		/**
		 * @brief Загрузить список доступных проектов
		 */
		void loadProjects();

		/**
		 * @brief Создать проект в облаке
		 */
		int createProject(const QString& _projectName);

		/**
		 * @brief Обновить название проекта
		 */
		void updateProjectName(int _projectId, const QString& _newProjectName);

		/**
		 * @brief Удалить проект
		 */
		void removeProject(int _projectId);

		/**
		 * @brief Добавить подписчика в свой проект
		 */
		void shareProject(int _projectId, const QString& _userEmail, int _role);

		/**
		 * @brief Убрать подписку на проект для заданного пользователя
		 * @note Если пользователь не задан, то происходит отписка текущего пользователя
		 */
		void unshareProject(int _projectId, const QString& _userEmail = QString::null);

	signals:
		/**
		 * @brief Авторизация пройдена успешно
		 */
		void loginAccepted(const QString& _userName, const QString& _userEmail);

		/**
		 * @brief Сервер успешно принял данные пользователя на регистрацию
		 */
		void signUpFinished();

		/**
		 * @brief Сервер подтвердил регистрацию
		 */
		void verified();

		/**
		 * @brief Пароль отправлен на email
		 */
		void passwordRestored();

		/**
		 * @brief Авторизация закрыта
		 */
		void logoutFinished();

		/**
		 * @brief Успешно изменено имя пользователя
		 */
		void userNameChanged();

		/**
		 * @brief Успешно запрошена информация о подписке
		 */
        void subscriptionInfoLoaded(bool _isActive, const QString& _expiredDate);

		/**
		 * @brief Успешно изменен пароль
		 */
		void passwordChanged();

		/**
		 * @brief Проекты загружены
		 */
		void projectsLoaded(const QString& _projectsXml);

		/**
		 * @brief Ошибка
		 */
		void syncClosedWithError(int, QString);

	private:
		/**
		 * @brief Проверка, что статус ответа - ок
		 */
		bool isOperationSucceed(QXmlStreamReader& _reader);

		/**
		 * Обработка ошибок
		 */
		void handleError(const QString& _error, int _code = 0);

	private:
		/**
		 * @brief Настроить соединения
		 */
		void initConnections();

	private:
		/**
		 * @brief указатель на главную форму приложения
		 */
		QWidget* m_view;

		/**
		 * Ключ сессии
		 */
		QString m_sessionKey;

		/**
		 * @brief Email пользователя
		 */
		QString m_userEmail;

		/**
		 * @brief Активна ли подписка у пользователя
		 */
		bool m_isSubscriptionActive;

		/**
		 * Загрузчик
		 */
        NetworkRequest* m_loader;
	};
}

#endif // SYNCHRONIZATIONMANAGERV2_H