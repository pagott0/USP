import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split

try:
    df = pd.read_excel("C:\\usp\\USP\\numericalCalculus\\expec_vida.xlsx", thousands=',')
except FileNotFoundError:
    print("Arquivo não encontrado. Certifique-se de que o arquivo está na mesma pasta do script.")
    exit()

# Separando as variáveis independentes (X) e a variável dependente (y)
X = df[['Renda per Cápita (US$)', 'PIB (US$ bilhões)', 'População (milhões)']]
y = df['Expectativa de Vida (anos)']

# Dividindo os dados em conjuntos de treinamento e teste (80% treino, 20% teste)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=16)

# Criando o modelo de regressão linear múltipla
model = LinearRegression()

# Treinando o modelo
model.fit(X_train, y_train)

# Fazendo previsões com os dados de teste
y_pred = model.predict(X_test)

# Calculando o erro médio quadrático (RMSE)
rmse = mean_squared_error(y_test, y_pred, squared=False)

# Imprimindo os resultados
print("Coeficientes:", model.coef_)
print("Intercepto:", model.intercept_)
print("RMSE:", rmse)

# Imprimindo as previsões e os valores reais para os países de teste
print("\nPrevisões vs. Valores Reais:")
for i in range(len(y_test)):
    print(f"País: {df.iloc[y_test.index[i]]['País']}, Previsão: {y_pred[i]:.2f}, Real: {y_test.iloc[i]:.2f}")