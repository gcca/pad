import CPad
import SwiftUI

struct ContentView: View {
    @State private var inputText = ""
    @State private var lines: [String] = []
    @FocusState private var inputFocused: Bool

    var body: some View {
        VStack(spacing: 0) {
            VStack(alignment: .leading, spacing: 0) {
                Text(lines.joined(separator: "\n"))
                if !inputText.isEmpty {
                    Text(quote(inputText))
                        .foregroundStyle(.secondary)
                }
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity, alignment: .topLeading)
            .padding()

            Divider()

            TextField("", text: $inputText)
                .textFieldStyle(.plain)
                .focused($inputFocused)
                .padding(8)
                .onSubmit {
                    lines.append(quote(inputText))
                    inputText = ""
                }

        }
        .onAppear {
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.1) {
                inputFocused = true
            }
        }

    }

    private func quote(_ text: String) -> String {
        var result = ""
        withUnsafeMutablePointer(to: &result) { ptr in
            pad_quote(
                text,
                { data, len, ctx in
                    let out = ctx!.assumingMemoryBound(to: String.self)
                    let bytes = UnsafeRawBufferPointer(start: data, count: len)
                    out.pointee = String(decoding: bytes, as: UTF8.self)
                }, ptr)
        }
        return result
    }
}
