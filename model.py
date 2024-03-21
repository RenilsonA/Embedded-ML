import pandas as pd
from sklearn.model_selection import train_test_split, KFold, cross_val_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

# Carregar os dados
data = pd.read_csv('database.csv')

# Dividir os dados em features (X) e target (y)
X = data.drop('classificacao', axis=1)
y = data['classificacao']

# Dividir os dados em conjunto de treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.02, random_state=42)

# Verificar a forma dos dados após a divisão
print("Forma dos dados de treinamento:", X_train.shape, y_train.shape)
print("Forma dos dados de teste:", X_test.shape, y_test.shape)

# Criar modelo preditivo
model_holdout = RandomForestClassifier(n_estimators=100, random_state=42, max_depth=None, min_samples_split=8)
model_holdout.fit(X_train, y_train)

# Avaliar o modelo
y_pred_holdout = model_holdout.predict(X_test)
accuracy_holdout = accuracy_score(y_test, y_pred_holdout)
print('Acurácia:', accuracy_holdout)

# Validacao cruzada
kf = KFold(n_splits=8, shuffle=True)
scores_cv = cross_val_score(model_holdout, X, y, cv=kf, scoring='accuracy')
print('Valores de cada validação:', scores_cv)
print('Média Floresta aleatoria:', scores_cv.mean())


data_app = pd.read_csv('test.csv')
model_holdout.fit(X, y)
y_pred = model_holdout.predict(data_app)
print(y_pred)