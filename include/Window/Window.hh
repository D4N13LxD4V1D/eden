#pragma once

class RawWindow {
public:
  RawWindow(const char *title, int width, int height);
  ~RawWindow();

  void show();

private:
  void *window;
};