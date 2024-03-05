import cv2
import numpy as np


# Leer los datos de entrada.
#Características del cubo hiperespectral: 1096x715x102
#Los píxeles se volcaron al fichero por columnas.

data = np.loadtxt('pavia.txt',delimiter=',')

# Convertir a un array NumPy
data_array = np.array(data)

print("Data array ",data_array.shape)

    
# Reorganizar los valores para adaptar a la entrada del kmeans
# Son 1096x715 pixeles, cada uno con 102 componentes.
matrix = np.reshape(data_array, (783640, 102))

# Los puntos de entrada para la primitiva kmeans deben ser de tipo punto flotante
pixels = matrix.astype(np.float32)

print("pixels array ",pixels.shape)

print("Empezando kmeans...")
# k-means 
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.2)
_, labels, centers = cv2.kmeans(pixels, 2, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)

print("labels array ",labels.shape)
print("centers array ",centers.shape)

#Reorganizamos las etiquetas en 715 filas y 1096 columnas.
#Recordar que los píxeles en el fichero estaban escritos en orde de
#las columnas. Así, al hacer posteriormente la trasnpuesta obtendremos la imagen correcta
cluster_map = np.reshape(labels, (715,1096)).astype(np.uint8)


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

# Asignar a cada pixel de la imagen de salida el color en finción de la etiqueta
result_image = np.zeros((1096,715, 3), dtype=np.uint8)

for i in range(result_image.shape[0]):
    for j in range(result_image.shape[1]):
        result_image[i, j] = color_map_array[cluster_map[j, i]]
        
#for cluster_index in range(10):
#    result_image[cluster_map == cluster_index] = color_map_array[cluster_index]

# Mostrar la imagen
cv2.imshow('Cluster image',result_image)
cv2.imwrite("paviakmeanspy.jpg",result_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

