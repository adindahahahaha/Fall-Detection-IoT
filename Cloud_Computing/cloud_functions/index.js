const functions = require('firebase-functions');
const admin = require('firebase-admin');

admin.initializeApp();

// Firestore Trigger: Detect when a new user is added
exports.newUserAdded = functions.firestore
    .document('users/{userId}')
    .onCreate((snap, context) => {
        const newUser = snap.data();
        console.log('New user added:', newUser);
    });

// HTTP Endpoint: Send notification
exports.sendNotification = functions.https.onRequest(async (req, res) => {
    const message = {
        notification: {
            title: 'Fall Detected!',
            body: 'A fall was detected. Please check immediately.',
        },
        topic: 'fall_alert',
    };

    try {
        await admin.messaging().send(message);
        res.status(200).send('Notification sent successfully!');
    } catch (error) {
        console.error('Error sending notification:', error);
        res.status(500).send('Notification failed.');
    }
});
