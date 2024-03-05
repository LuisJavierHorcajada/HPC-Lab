import time
import cv2
import numpy as np
import argparse

def argparser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-k", "--kmeans", dest="K", type=int, required=True, help="Kmeans size")
    args = parser.parse_args()
    K = args.K
    return K

def kmeans(data, K):
    # Se inicializan los centroides aleatoriamente eligiendo K puntos de los datos
    indices = np.random.choice(data.shape[0], K, replace=False)
    centroids = data[indices]

    # Copia de centroides para su posterior comparación
    prev_centroids = centroids.copy()

    max_iterations = 100
    tolerance = 0.2
    for i in range(max_iterations):
        # Se asignan los datos a cada centroide según su distancia
        distances = np.linalg.norm(data[:, np.newaxis] - centroids, axis=2)
        labels = np.argmin(distances, axis=1)

        # Se actualiza la posición de cada centroide en función de la cantidad de datos de cada uno
        centroids = np.zeros((K, data.shape[1]))
        for j in range(K):
            cluster_points = data[labels == j]
            if len(cluster_points) > 0:
                centroids[j] = np.mean(cluster_points, axis=0)

        # Se comprueba la distancia con los centroides anteriores
        if np.linalg.norm(centroids - prev_centroids) < tolerance:
            break

        prev_centroids = centroids.copy()

    return labels, centroids

def run_kmeans(data, K):
    print(f'\nEmpezando kmeans con {K} clusters...')
    start_time = time.time()
    labels, centroids = kmeans(data, K)
    end_time = time.time()
    execution_time = end_time - start_time
    return labels, centroids, execution_time

if __name__ == "__main__":
    K = argparser()

    # Leer los datos de entrada.
    data = np.loadtxt('pavia.txt', delimiter=',')

    # Convertir a un array NumPy
    data_array = np.array(data)

    print("Data array ", data_array.shape)

    # Reorganizar los valores para adaptar a la entrada del kmeans
    # Son 1096x715 pixeles, cada uno con 102 componentes.
    matrix = np.reshape(data_array, (783640, 102))

    # Los puntos de entrada para la primitiva kmeans deben ser de tipo punto flotante
    pixels = matrix.astype(np.float32)

    print("pixels array ", pixels.shape)

    kmeans_start_time = time.time()
    labels,centroids, execution_time=run_kmeans(pixels, K)
    print(f'\nTiempo final con {K} clusters:   {str(execution_time)} segundos')
    print("labels array ", labels.shape)
    print("centers array ", centroids.shape)

    # Reorganizamos las etiquetas en 715 filas y 1096 columnas.
    cluster_map = np.reshape(labels, (715, 1096)).astype(np.uint8)

    # Mapa de color (B, G, R) en OpenCV
    colors = [
        (0, 0, 255),   # Red
        (0, 255, 0),   # Green
        (255, 0, 0),   # Blue
        (255, 255, 0), # Yellow
        (255, 0, 255), # Magenta
        (0, 255, 255), # Cyan
        (255, 255, 255), # White
        (0, 0, 0),     # Black
        (128, 128, 128), # Gray
        (64, 64, 64)   # Gray
    ]

    color_map_array = np.array(colors)

    # Asignar a cada pixel de la imagen de salida el color en función de la etiqueta
    result_image = np.zeros((1096, 715, 3), dtype=np.uint8)

    for i in range(result_image.shape[0]):
        for j in range(result_image.shape[1]):
            result_image[i, j] = color_map_array[cluster_map[j, i]]

    # Mostrar la imagen
    cv2.imshow('Cluster image', result_image)
    cv2.imwrite("paviakmeanspy2.jpg", result_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

