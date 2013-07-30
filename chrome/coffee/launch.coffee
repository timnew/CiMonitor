chrome.app.runtime.onLaunched.addListener ->
  chrome.app.window.create '/html/index.html',
    bounds:
      top: 0
      left: 0