print("Successfully passed this Python program from C++!")


import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

# import private key
# path/to/serviceAccount.json 請用自己存放的路徑
cred = credentials.Certificate('./serviceAccount.json')

# init firebase /* MENTION: one should not init repeatly */
firebase_admin.initialize_app(cred)

# init firestore
db = firestore.client()