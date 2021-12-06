import cv2
import numpy as np


def load_data(filename):
  file = open(filename, mode='r')
  data = file.read()
  file.close()
  size, data = data.split("\n", 1)
  size = int(size)
  data = data.replace("H", "0")
  data = data.replace("1", "1")
  data = data.replace("S", "2")
  data = data.replace("X", "3")
  data = data.replace("D", "4")
  data = data.replace("\n", "")
  data = list(data)
  data = np.array(data, dtype=np.uint8)
  data = data.reshape((data.shape[0]//(size*size), size, size))
  return data


def show_video(video, outfile=None, speed=0):
  lut = np.zeros((1, 256, 3), np.dtype('uint8'))
  lut[0, 0, 1] = 255
  lut[0, 1, 2] = 255
  lut[0, 2, 2] = 170
  lut[0, 3, 2] = 90
  lut[0, 4, 2] = 0

  if outfile is not None:
    # Tady zmen tu 10 na jine cislo pro jina FPSka, + bacha, ty videa jsou velke mrsky
    out = cv2.VideoWriter(outfile,
                             cv2.VideoWriter_fourcc(*'mp4v'),
                             10, (1000, 1000))
  for frame in video:
    frame = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)
    frame = cv2.LUT(frame, lut)

    if outfile is not None:
      out.write(frame)
    cv2.imshow("frame", frame)
    k = cv2.waitKey(speed)
    if k == ord("q"):
      return

  if outfile is not None:
    out.release()


if __name__ == "__main__":
  video = load_data("automatVideo.txt")
  # cim vetsi je parametr speed, ten posledni, tim pomalejsi to bude(speed == wait v ms)
  # pri speed == 0, musis odklikavat sam,
  # Qckem vypnes program
  # pri None misto mista pro ulozeni, se jen vymaluje a nic se neuklada
  # RYCHLOST TADY NEOVLIVNUJE FPS VIDEA, to je parametr u cv2.VideoWriter uvnitr funkce
  # u toho je to popsane
  show_video(video, "./vysledek.mp4", 10)
