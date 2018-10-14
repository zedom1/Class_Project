import os
import pickle
import numpy as np 
from PIL import Image
from feature import NPDFeature
from ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
def processImage(im):
	im = im.convert('L')
	im = im.resize((24,24))
	return NPDFeature(np.array(im)).extract()

def getData():
	X = []
	y = []
	if os.path.exists("./data_x") and os.path.exists("./data_y"):
		with open("./data_x", "rb") as f:
			X = pickle.load(f)
		with open("./data_y", "rb") as f:
			y = pickle.load(f)
	else:
		path_face = './datasets/original/face/'
		path_non_face = './datasets/original/nonface/'
		for i in os.listdir(path_face):
			features = processImage(Image.open(path_face+i))
			X.append(features)
			y.append(1)

		for i in os.listdir(path_non_face):
			features = processImage(Image.open(path_non_face+i))
			X.append(features)
			y.append(0)
		with open("data_x", "wb") as f:
			pickle.dump(X, f)
		with open("data_y", "wb") as f:
			pickle.dump(y, f)
	return X,y

if __name__ == "__main__":

	X,y = getData()
	X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, shuffle=True)
	clf = AdaBoostClassifier(DecisionTreeClassifier, 10)
	clf.fit(X_train, y_train)
	predict = clf.predict(X_val)
	print(classification_report(y_val, predict))
