// import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
// import './index.css'
// import App from "./App.tsx";
import Router from "./routes/index.tsx";
import {
  QueryClient,
  QueryClientProvider,
  // useQuery,
} from "@tanstack/react-query";
// import { ReactQueryDevtools } from "@tanstack/react-query-devtools";

const queryClient = new QueryClient();

createRoot(document.getElementById("root")!).render(
  // <StrictMode>
  <QueryClientProvider client={queryClient}>
    <Router />
  </QueryClientProvider>
  // </StrictMode>
);
