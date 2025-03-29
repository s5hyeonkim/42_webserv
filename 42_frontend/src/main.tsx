// import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import Router from "./routes/index.tsx";
import {
  QueryClient,
  QueryClientProvider,
  // useQuery,
} from "@tanstack/react-query";
import { AuthProvider } from "./Auth.tsx";

const queryClient = new QueryClient();

createRoot(document.getElementById("root")!).render(
  // <StrictMode>
  <AuthProvider>
    <QueryClientProvider client={queryClient}>
      <Router />
    </QueryClientProvider>
  </AuthProvider>
  // </StrictMode>
);
