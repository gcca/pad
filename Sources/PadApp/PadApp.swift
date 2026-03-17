import SwiftUI

@main
struct PadApp: App {
  @Environment(\.scenePhase) private var scenePhase

  init() {
    #if os(macOS)
    NSApplication.shared.setActivationPolicy(.regular)
    #endif
  }

  var body: some Scene {
    WindowGroup("Pad") {
      ContentView()
        #if os(macOS)
        .toolbarBackgroundVisibility(.hidden, for: .windowToolbar)
        #endif
        .onAppear {
          #if os(macOS)
          DispatchQueue.main.async {
            NSApplication.shared.activate(ignoringOtherApps: true)
            if let window = NSApplication.shared.windows.first {
              window.makeKeyAndOrderFront(nil)
              window.titlebarAppearsTransparent = true
            }
          }
          #endif
        }
    }
    #if os(macOS)
    .onChange(of: scenePhase) {
      if scenePhase == .background {
        NSApplication.shared.terminate(nil)
      }
    }
    #endif
  }
}
