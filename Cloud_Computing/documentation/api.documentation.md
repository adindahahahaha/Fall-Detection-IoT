# API Documentation

## Endpoints

### 1. **Firestore Trigger**
**Trigger:** `/users/{userId}`  
**Description:** Triggered when a new user document is added. Logs the user data to the console.

---

### 2. **HTTP Endpoint**
**Endpoint:** `/sendNotification`  
**Method:** POST  
**Description:** Sends a notification to all devices subscribed to the `fall_alert` topic.  
**Payload:**
```json
{
  "title": "Fall Detected!",
  "body": "A fall was detected. Please check immediately."
}
