# API Documentation for Cloud Computing Project

This document describes the available APIs and triggers for the project.

---

## **1. Firestore Trigger: New User Added**

**Trigger:**  
Fires when a new user document is added to the `users` collection in Firestore.

**Path:**  
`users/{userId}`

**Description:**  
Logs the newly added user to the console and performs any necessary operations like subscribing the user to a notification topic.

**Example Document:**
```json
{
  "userId": "12345",
  "name": "John Doe",
  "email": "johndoe@example.com"
}
```

---

## **2. HTTP Endpoint: Send Notification**

**Method:**  
`POST`

**URL:**  
`https://<region>-<project-id>.cloudfunctions.net/sendNotification`

**Description:**  
Sends a notification to all devices subscribed to the `fall_alert` topic.

**Request Example:**
```bash
curl -X POST https://<region>-<project-id>.cloudfunctions.net/sendNotification
```

**Response:**
- **Success (200):**  
  ```json
  {
    "message": "Notification sent successfully!"
  }
  ```

- **Error (500):**  
  ```json
  {
    "error": "Notification failed."
  }
  ```

---

## **3. Example Firestore Structure**

### **`users` Collection**
Stores user information:
```json
{
  "userId": "unique_user_id",
  "name": "John Doe",
  "token": "device_fcm_token"
}
```

### **`fallEvents` Collection**
Stores fall detection events:
```json
{
  "eventId": "unique_event_id",
  "userId": "user_id",
  "isFallDetected": true,
  "timestamp": "2024-12-07T00:00:00Z"
}
```

---

## **4. Topics for Notifications**

### **Topic: `fall_alert`**
Devices subscribed to this topic receive notifications for detected falls.

**Notification Payload:**
```json
{
  "notification": {
    "title": "Fall Detected!",
    "body": "A fall was detected. Please check immediately."
  },
  "topic": "fall_alert"
}
```

---

## **5. Error Codes**

| Code | Description                 |
|------|-----------------------------|
| 200  | Notification sent successfully |
| 500  | Failed to send notification |

---

### **How to Use**
- Save this file as `api_documentation.md` in the `documentation` folder.
- Replace placeholders like `<region>` and `<project-id>` with your actual Firebase details.
