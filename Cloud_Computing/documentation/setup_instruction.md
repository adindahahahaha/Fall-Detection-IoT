# Setup Instructions for Cloud Computing Project

Here's a step-by-step guide to set up and deploy the project, including backend services, Firebase configuration, and any dependencies.

---

## **1. Prerequisites**

Before starting, ensure you have the following installed:
- [Node.js](https://nodejs.org/) (version 16 or higher)
- [Firebase CLI](https://firebase.google.com/docs/cli)
- [Git](https://git-scm.com/)
- A Google account to access Firebase Console

---

## **2. Clone the Repository**

Clone the project to your local machine using the following command:
```bash
git clone https://github.com/your-repo.git
cd Cloud_Computing
```

---

## **3. Firebase Configuration**

### 3.1 Install Firebase CLI
Install Firebase CLI globally:
```bash
npm install -g firebase-tools
```

### 3.2 Log in to Firebase
Log in to your Firebase account:
```bash
firebase login
```

### 3.3 Initialize Firebase in the Project
Navigate to the `cloud_functions` directory and initialize Firebase:
```bash
cd cloud_functions
firebase init
```

During the initialization process:
- Enable **Cloud Functions** and **Firestore**.
- Choose **JavaScript** as the language for Cloud Functions.
- Use the default options for other services unless specific configurations are required.

### 3.4 Set Up Environment Variables
1. Create a `.env` file in the `cloud_functions` directory.
2. Add your Firebase project credentials in the following format:
   ```env
   API_KEY=your_api_key
   PROJECT_ID=your_project_id
   SENDER_ID=your_sender_id
   APP_ID=your_app_id
   ```

Replace `your_api_key`, `your_project_id`, `your_sender_id`, and `your_app_id` with your Firebase project's actual values.

---

## **4. Install Dependencies**

Navigate to the `cloud_functions` directory and install the required dependencies:
```bash
npm install
```

---

## **5. Deploy Cloud Functions**

To deploy the Firebase Cloud Functions to the cloud, run the following command:
```bash
firebase deploy --only functions
```

---

## **6. Configure Firestore Rules**

Ensure your Firestore security rules are properly configured. Open the `firebase_config/firestore.rules` file and confirm the rules look like this:
```plaintext
rules_version = '2';
service cloud.firestore {
  match /databases/{database}/documents {
    match /users/{userId} {
      allow read, write: if request.auth != null;
    }
    match /fallEvents/{eventId} {
      allow read, write: if request.auth != null;
    }
  }
}
```

Deploy the Firestore rules:
```bash
firebase deploy --only firestore
```

---

## **7. Testing**

### 7.1 Firestore Trigger Test
1. Add a new document to the `users` collection in Firestore.
2. Check the Firebase logs to confirm the `newUserAdded` function was triggered:
   ```bash
   firebase functions:log
   ```

### 7.2 HTTP Endpoint Test
Test the notification endpoint using `curl` or Postman. For example:
```bash
curl -X POST https://<region>-<project-id>.cloudfunctions.net/sendNotification
```

---

## **8. Additional Notes**

### Documentation
- For API details, refer to the `api.documentation.md` file.
- For the architecture diagram, see `architecture_diagram.png`.

### Troubleshooting
If you encounter any issues, check the Firebase logs:
```bash
firebase functions:log
```

For further debugging, ensure all Firebase services are enabled in the Firebase Console.

---

### **How to Use**
1. Save this file as `setup_instruction.md` in the `documentation` folder of your GitHub project.
2. Update placeholders like `your-repo`, `your_api_key`, and `your_project_id` with actual values from your Firebase project.
