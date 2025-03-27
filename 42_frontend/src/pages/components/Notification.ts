// import create from "zustand";

// interface NotificationStore {
//   notifications: string[];
//   addNotification: (message: string) => void;
//   removeNotification: (message: string) => void;
//   resetNotifications: () => void;
// }

// const useNotificationStore = create<NotificationStore>((set) => ({
//   notifications: [],
//   addNotification: (message: string) =>
//     set((state) => ({
//       notifications: [...state.notifications, message],
//     })),
//   removeNotification: (message: string) =>
//     set((state) => ({
//       notifications: state.notifications.filter((msg) => msg !== message),
//     })),
//   resetNotifications: () => set({ notifications: [] }),
// }));

// export default useNotificationStore;
