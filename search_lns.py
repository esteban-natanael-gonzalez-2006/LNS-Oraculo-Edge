import ctypes, numpy as np, time

lib = ctypes.CDLL('./liblnsindex.so')
search = lib.lns_search_flat
search.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int8), ctypes.POINTER(ctypes.c_int8), ctypes.POINTER(ctypes.c_int32)]

N, D = 100000, 768
db = np.random.randint(-127, 127, N*D, dtype=np.int8)
q = np.random.randint(-127, 127, D, dtype=np.int8)
scores = np.zeros(N, dtype=np.int32)

print(f"\n[+] Buscando 1 Query contra {N} Documentos (Dim {D}) en Silicio LNS...")
st = time.perf_counter_ns()
search(N, D, q.ctypes.data_as(ctypes.POINTER(ctypes.c_int8)), db.ctypes.data_as(ctypes.POINTER(ctypes.c_int8)), scores.ctypes.data_as(ctypes.POINTER(ctypes.c_int32)))
tiempo = (time.perf_counter_ns() - st) / 1e6

print(f"[V] FAISS Bypass Completo: {tiempo:.2f} ms")
print(f"[!] Top 5 Documentos Relevantes: {np.argsort(scores)[-5:][::-1]}")
